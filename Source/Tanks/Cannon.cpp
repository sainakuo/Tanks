// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "DamageTarget.h"
#include "DrawDebugHelpers.h"


// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	//таймер, который запускает серию выстрелов, если bStartToShootSeries = 1
	GetWorld()->GetTimerManager().SetTimer(TimerHandleForSeries, FTimerDelegate::CreateUObject(this, &ACannon::FireSeriesTick), 1/FireRateSeries, true);
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GEngine->AddOnScreenDebugMessage(123, 10, FColor::Yellow, FString(TEXT("TOTAL: ")) + FString::Printf(TEXT("%d"), ProjectileCount));
	
}

void ACannon::ResetShootState()
{
	bReadyToShoot = true;
}

void ACannon::StartShootTimer()
{
	bReadyToShoot = false;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ACannon::ResetShootState), 1/FireRate, false);
}

void ACannon::ProjectileDecrease()
{
	if (ProjectileCount > 0)
		ProjectileCount--;

	if (ProjectileCount == 0)
		bProjectileStock = false;
}

void ACannon::Shoot()
{
	if (!bReadyToShoot || !bProjectileStock)
		return;
	
	switch (Type)
	{
	case ECannonType::FireProjectile:
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString(TEXT("Puf-Puf")));
		break;
	case ECannonType::FireTrace:
		auto Start = ProjectileSpawnPoint->GetComponentLocation();
		auto End = Start + ProjectileSpawnPoint->GetForwardVector()*FireRange;
		FCollisionObjectQueryParams Params;
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_Vehicle);
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		
		FHitResult Result;
		bool HasHit = GetWorld()->LineTraceSingleByObjectType(Result, Start, End, Params);

		if (HasHit)
		{
			End = Result.Location;
			if (Result.Actor.IsValid())
			{
				auto Target = Cast<IDamageTarget>(Result.Actor);
				if (Target)
				{
					FDamageData DamageData;
					DamageData.Instigator = this;
					DamageData.DamageValue = LaserDamage;
					Target -> TakeDamage(DamageData);
				}
			}
		}

		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1, 0, 10);
		
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString(TEXT("Piu-Piu")));
		break;
	}
	ProjectileDecrease();
	StartShootTimer();
}

void ACannon::FireSpecial()
{
	if (!bReadyToShoot || !bProjectileStock)
		return;
	
	switch (Type)
	{
	case ECannonType::FireProjectile:
		GetWorld()->SpawnActor<AProjectile>(ProjectileClassSpecial, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString(TEXT("Puf-Puf SPECIAL")));
		break;
	case ECannonType::FireTrace:
		auto Start = ProjectileSpawnPoint->GetComponentLocation();
		auto End = Start + ProjectileSpawnPoint->GetForwardVector()*FireRange;
		FCollisionObjectQueryParams Params;
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_Vehicle);
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		
		FHitResult Result;
		bool HasHit = GetWorld()->LineTraceSingleByObjectType(Result, Start, End, Params);

		if (HasHit)
		{
			End = Result.Location;
			if (Result.Actor.IsValid())
			{
				auto Target = Cast<IDamageTarget>(Result.Actor);
				if (Target)
				{
					FDamageData DamageData;
					DamageData.Instigator = this;
					DamageData.DamageValue = LaserDamage;
					Target -> TakeDamage(DamageData);
				}
			}
			
		}

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1, 0, 15);
		
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString(TEXT("Piu-Piu SPECIAL")));
		break;
	}
	ProjectileDecrease();
	StartShootTimer();
}

void ACannon::StartFireSeries()
{
	if (bReadyToShoot && bProjectileStock)
	{
		bReadyToShoot = false;
		bStartToShootSeries = true;
	}
}

void ACannon::FireSeriesTick()
{
	if (bStartToShootSeries)
	{
		if (FireCountInSeriesLocal > 0)
		{
			switch (Type)
			{
			case ECannonType::FireProjectile:
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("Puf-Puf SERIES")));
				break;
			case ECannonType::FireTrace:
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("Piu-Piu SERIES")));
				break;
			}
			FireCountInSeriesLocal--;
		}
	
		if (FireCountInSeriesLocal == 0)
		{
			FireCountInSeriesLocal = FireCountInSeries;
			ProjectileDecrease();
			bReadyToShoot = true;
			bStartToShootSeries = false;
		}
	}
}
