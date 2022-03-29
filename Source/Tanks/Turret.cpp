// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "DrawDebugHelpers.h"
#include "Commandlets/EditorCommandlets.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	RootComponent = Collision;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("BodyMesh");
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BodyMesh);

	RangeSphere = CreateDefaultSubobject<USphereComponent>("RangeSphere");
	RangeSphere->SetupAttachment(RootComponent);

	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnBeginOverlap);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnEndOverlap);

	CannonPosition = CreateDefaultSubobject<UArrowComponent>("CannonPosition");
	CannonPosition->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ATurret::OnDeath);
}

void ATurret::TakeDamage(FDamageData Damage)
{
	if (HealthComponent)
		HealthComponent->TakeDamage(Damage);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ATurret::Targeting, TargetingRate, true);

	if (CannonClass)
	{
		Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, CannonPosition->GetComponentTransform());
		Cannon->AttachToComponent(CannonPosition, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void ATurret::Destroyed()
{
	Super::Destroyed();

	if (Cannon)
		Cannon->Destroy();
}

void ATurret::OnBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                             UPrimitiveComponent* OtherComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	OtherActors.Add(Actor);

	if (!Target.IsValid())
	{
		FindNextTarget();
	}
}

void ATurret::OnEndOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* OtherComponent1, int I)
{
	OtherActors.Remove(Actor);

	if (Actor == Target)
	{
		FindNextTarget();
	}
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::FindNextTarget()
{
	float MinRange = 100000;
	Target = nullptr;
	for (auto Actor: OtherActors)
	{
		float Range = FVector::Distance(Actor->GetActorLocation(), GetActorLocation());
		if (Range < MinRange)
		{
			MinRange = Range;
			Target = Actor;
		}
	}
}

void ATurret::Fire()
{
	if (!Target.IsValid())
		return;

	FHitResult Result;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(Cannon);
	Params.bTraceComplex = true;
	
	if (GetWorld()->LineTraceSingleByChannel(Result, TurretMesh->GetComponentLocation(), Target->GetActorLocation(), ECollisionChannel::ECC_Visibility, Params))
	{
		if (Result.Actor == Target.Get())
		{
			if (Cannon)
				Cannon->Shoot();
		}
	}
}

void ATurret::Targeting()
{
	if (!Target.IsValid())
	{
		FindNextTarget();
		if (!Target.IsValid())
		{
			return;
		}
	}

	auto TargetRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), Target->GetActorLocation());
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretMesh->GetComponentRotation(), TargetRotation, TargetingSpeed));

	auto TargetingDirection = TurretMesh->GetForwardVector();
	auto PlayerDirection = Target->GetActorLocation() - GetActorLocation();

	PlayerDirection.Normalize();

	auto Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetingDirection, PlayerDirection)));

	if (Angle < AimSlack)
	{
		ATurret::Fire();
	}
	
}

void ATurret::OnDeath()
{
	Destroy();
}

