// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Tanks.h"

#include <string>

#include "TankPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonPosition = CreateDefaultSubobject<UArrowComponent>("Cannon pos");
	CannonPosition->SetupAttachment(TurretMesh);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ATankPawn::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankPawn::OnHealthChanged);

	
	DamageEffect = CreateDefaultSubobject<UParticleSystemComponent>("DamageEffect");
	DamageEffect->SetupAttachment(BodyMesh);

	DestructionEffect = CreateDefaultSubobject<UParticleSystemComponent>("DestructionEffect");
	DestructionEffect->SetupAttachment(BodyMesh);
	
}

void ATankPawn::SetupCannon(bool CannonNumber)
{

	if (CannonNumber == 0)
	{
		CurrentCannon = 1;
		ChangeCannon();
	}
	else if (CannonNumber == 1)
	{
		CurrentCannon = 0;
		ChangeCannon();
	}
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, CannonPosition->GetComponentTransform());
	Cannon->AttachToComponent(CannonPosition, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	CannonSecond = GetWorld()->SpawnActor<ACannon>(CannonTypeSecond, CannonPosition->GetComponentTransform());
	CannonSecond->AttachToComponent(CannonPosition, FAttachmentTransformRules::SnapToTargetIncludingScale);
	CannonSecond->SetActorHiddenInGame(true); //hide the second cannon

	if (IsValid(GameOverWidgetClass))
	{
		GameOverWidget = CreateWidget(GetWorld(), GameOverWidgetClass);
	}
}

void ATankPawn::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
	
	if (CannonSecond)
		CannonSecond->Destroy();
}


void ATankPawn::TakeDamage(FDamageData Damage)
{
	if (HealthComponent)
		HealthComponent->TakeDamage(Damage);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveTank(DeltaTime);
	
	RotateTank(DeltaTime);

	RotateCannon(DeltaTime);

}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankPawn::MoveForward(float Scale)
{
	MoveScaleTarget = Scale;
}

void ATankPawn::RotateRight(float Scale)
{
	RotateScaleTarget = Scale;
}

void ATankPawn::MoveTank(float DeltaTime)
{
	MoveScaleCurrent = FMath::Lerp(MoveScaleCurrent, MoveScaleTarget, MovementAcceleration);
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation + MoveScaleCurrent*forwardVector*MoveSpeed*DeltaTime;
	SetActorLocation(movePosition, true);
	//GEngine->AddOnScreenDebugMessage(1234, 10, FColor::Blue, FString::Printf(TEXT("%f"), MoveScaleCurrent));
}

void ATankPawn::RotateTank(float DeltaTime)
{
	RotateScaleCurrent = FMath::Lerp(RotateScaleCurrent, RotateScaleTarget, RotationAcceleration);
	FRotator currentRotation = GetActorRotation();
	currentRotation.Yaw += RotateScaleCurrent*RotationSpeed*DeltaTime;
	SetActorRotation(currentRotation);
	//UE_LOG(LogTanks, Warning, TEXT("%s"), *currentRotation.ToString());
}

void ATankPawn::RotateCannon(float DeltaTime)
{
	if (!TankController)
		return;
	auto OldRotation = TurretMesh->GetComponentRotation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), TankController->GetShootTarget());
    OldRotation.Yaw = TurretRotation.Yaw;
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretMesh->GetComponentRotation(), OldRotation, TurretAcceleration ));
}

void ATankPawn::PrintProjectile()
{
	GEngine->AddOnScreenDebugMessage(123, 10, FColor::Yellow, FString(TEXT("TOTAL CANNON: ")) + FString::Printf(TEXT("%d"), Cannon->ProjectileCount));
	GEngine->AddOnScreenDebugMessage(12345, 10, FColor::Yellow, FString(TEXT("TOTAL CANNON SECOND: ")) + FString::Printf(TEXT("%d"), CannonSecond->ProjectileCount));
}

void ATankPawn::OnDeath()
{
	DestructionEffect->ActivateSystem();
	Destroy();
	GameOverWidget->AddToViewport();
	//UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}


void ATankPawn::OnHealthChanged(float CurrentHealth)
{
	DamageEffect->ActivateSystem();
	GEngine->AddOnScreenDebugMessage(12333, 10, FColor::Red, FString::Printf(TEXT("Health: %f"), CurrentHealth));
}

void ATankPawn::Shoot()
{
	if (CurrentCannon == 0 && Cannon)
	{
		Cannon->Shoot();
	}
	else if (CurrentCannon == 1 && CannonSecond)
	{
		CannonSecond->Shoot();
	}
	
	PrintProjectile();
}

void ATankPawn::FireSpecial()
{
	if (CurrentCannon == 0 && Cannon)
	{
		Cannon->FireSpecial();
	}
	else if (CurrentCannon == 1 && CannonSecond)
	{
		CannonSecond->FireSpecial();
	}
	
	PrintProjectile();
}

void ATankPawn::StartFireSeries()
{
	if (CurrentCannon == 0 && Cannon)
	{
		Cannon->StartFireSeries();
	}
	else if (CurrentCannon == 1 && CannonSecond)
	{
		CannonSecond->StartFireSeries();
	}
	PrintProjectile();
}

void ATankPawn::ChangeCannon()
{
	if (CurrentCannon == 0 && Cannon)
	{
		Cannon -> SetActorHiddenInGame(true);
		CannonSecond -> SetActorHiddenInGame(false);
		CurrentCannon = 1;
	}
	else if (CurrentCannon == 1 && CannonSecond)
	{
		Cannon -> SetActorHiddenInGame(false);
		CannonSecond -> SetActorHiddenInGame(true);
		CurrentCannon = 0;
	}
}

void ATankPawn::ProjectilePlus(int num)
{
	if (CurrentCannon == 0 && Cannon)
	{
		Cannon->ProjectileCount += num;
	}
	else if (CurrentCannon == 1 && CannonSecond)
	{
		CannonSecond->ProjectileCount += num;
	}
	
	PrintProjectile();
}

void ATankPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	TankController = Cast<ATankPlayerController>(GetController());
}