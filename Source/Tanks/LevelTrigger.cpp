// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelTrigger::ALevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	RootComponent = TriggerBox;
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelTrigger::OnOverlapTrigger);

	InactiveLight = CreateDefaultSubobject<USpotLightComponent>("InactiveLight");
	InactiveLight->SetupAttachment(RootComponent);

	ActiveLight = CreateDefaultSubobject<USpotLightComponent>("ActiveLight");
	ActiveLight->SetupAttachment(RootComponent);

	

}

void ALevelTrigger::SetActive(bool Active)
{
	InactiveLight->SetHiddenInGame(Active);
	ActiveLight->SetHiddenInGame(!Active);
	
	isActive = Active;
}

// Called when the game starts or when spawned
void ALevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTrigger::OnOverlapTrigger(UPrimitiveComponent* Component, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int I, bool bArg, const FHitResult& HitResult)
{
	if (isActive && !LevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

