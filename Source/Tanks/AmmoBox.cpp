// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"

#include "TankPawn.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	RootComponent = Collision;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAmmoBox::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAmmoBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast<ATankPawn>(OtherActor);

	if (Tank)
	{
		Tank->SetupCannon(CannonClass);
		Tank->ProjectilePlus(ProjectilePlusNum);
		
		if (!bInfinity)
			Destroy();
	}
	

		
}


