// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tanks.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);

		InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);

		InputComponent->BindAction("Shoot", IE_Pressed, this,  &ATankPlayerController::OnShoot);

		InputComponent->BindAction("Shoot2", IE_Pressed, this,  &ATankPlayerController::FireSpecial);

		InputComponent->BindAction("FireSeries", IE_Pressed, this,  &ATankPlayerController::StartFireSeries);

		InputComponent->BindAction("ChangeCannon", IE_Pressed, this,  &ATankPlayerController::ChangeCannon);

		InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ThisClass::OnLeftMouseButtonUp);
	}

	bShowMouseCursor = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());

	bEnableClickEvents = true;
}

void ATankPlayerController::OnLeftMouseButtonUp()
{
	OnMouseButtonUp.Broadcast();
}

void ATankPlayerController::MoveForward(float Scale)
{
	TankPawn->MoveForward(Scale);
}

void ATankPlayerController::RotateRight(float Scale)
{
	TankPawn->RotateRight(Scale);
}

void ATankPlayerController::OnShoot()
{
	TankPawn->Shoot();
}

void ATankPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}

void ATankPlayerController::StartFireSeries()
{
	TankPawn->StartFireSeries();
}

void ATankPlayerController::ChangeCannon()
{
	TankPawn->ChangeCannon();
}




void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector MousePosition, MouseDirection;

	
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);
	
	auto Z = FMath::Abs(TankPawn->GetActorLocation().Z - MousePosition.Z);
	MouseWorldPosition = MousePosition - MouseDirection * Z / MouseDirection.Z;
	
	//DrawDebugSphere(GetWorld(), MousePosition, 3, 16, FColor::Red);
	//DrawDebugLine(GetWorld(), MousePosition, MousePosition+MouseDirection*5000, FColor::Red);

	//math case
	//DrawDebugSphere(GetWorld(), MouseWorldPosition, 3, 16, FColor::Green);
	
}

FVector ATankPlayerController::GetShootTarget() const
{
	return MouseWorldPosition;
}


