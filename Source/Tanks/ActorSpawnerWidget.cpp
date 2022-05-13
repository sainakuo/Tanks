// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWidget.h"

#include "TankPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UActorSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (auto* MyController = Cast<ATankPlayerController>(PlayerController))
	{
		MyController->OnMouseButtonUp.AddUObject(this, &ThisClass::OnMouseButtonUp);
	}
}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePosition;
		FVector WorldMouseDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		FHitResult OutHit;

		constexpr float Dist = 100000.f;

		GetWorld()->LineTraceSingleByChannel(OutHit, WorldMousePosition, WorldMousePosition+WorldMouseDirection*Dist, ECollisionChannel::ECC_WorldStatic, Params);

		OutHit.Location.Z = 8617;
		
		if (OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location);
		}
	}
	
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass);
		auto SpawnedTurret = Cast<ATurret>(SpawnedActor);
		SpawnedTurret->IsFriend = true;
	}
	return FReply::Handled();
}

void UActorSpawnerWidget::OnMouseButtonUp()
{
	SpawnedActor = nullptr;
}
