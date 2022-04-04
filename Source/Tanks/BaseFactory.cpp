// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFactory.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABaseFactory::ABaseFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	BuildingMesh->SetupAttachment(RootComponent);

	HitCollider = CreateDefaultSubobject<UBoxComponent>("HitCollider");
	HitCollider->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDeath.AddUObject(this, &ABaseFactory::onDeath);

	TankSpawnEffect = CreateDefaultSubobject<UParticleSystemComponent>("TankSpawnEffect");
	TankSpawnEffect->SetupAttachment(RootComponent);

	DestructionEffect = CreateDefaultSubobject<UParticleSystemComponent>("DestructionEffect");
	DestructionEffect->SetupAttachment(RootComponent);

}

void ABaseFactory::TakeDamage(FDamageData Damage)
{
	if (HealthComponent)
		HealthComponent->TakeDamage(Damage);
}

// Called when the game starts or when spawned
void ABaseFactory::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandler, this, &ABaseFactory::OnTankSpawnTick, SpawnInterval, true);
	
	
}

// Called every frame
void ABaseFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFactory::OnTankSpawnTick()
{
	auto Tank = GetWorld()->SpawnActorDeferred<AEnemyTankPawn>(TankClass, SpawnPoint->GetComponentTransform());
	Tank->Waypoints = Waypoints;
	TankSpawned++;
	
	Tank->Number = TankSpawned;

	UGameplayStatics::FinishSpawningActor(Tank, SpawnPoint->GetComponentTransform());

	TankSpawnEffect->ActivateSystem();
}

void ABaseFactory::onDeath()
{
	DestructionEffect->ActivateSystem();
	GetWorldTimerManager().SetTimer(TimerBeforeDeath, this, &ABaseFactory::onDeathAfterDestructionEffect, 0.5, false);
	
}

void ABaseFactory::onDeathAfterDestructionEffect()
{
	Destroy();
	GetWorldTimerManager().ClearTimer(TimerHandler);
	GetWorldTimerManager().ClearTimer(TimerBeforeDeath);

	if (LevelTrigger)
		LevelTrigger->SetActive(true);
}

