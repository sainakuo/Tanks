// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "DrawDebugHelpers.h"
#include "TankPawn.h"
#include "WaypointActor.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!TankPawn)
		return;

	FVector CurrentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	FVector PawnLocation = GetPawn()->GetActorLocation();

	if (FVector::Distance(CurrentPoint, PawnLocation) < MovementAccuracy)
	{
		CurrentPatrolPointIndex++;
		if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
		{
			CurrentPatrolPointIndex = 0;
		}
	}

	FVector Direction = CurrentPoint - PawnLocation;
	Direction.Normalize();

	auto ForwardVector = TankPawn->GetActorForwardVector();
	auto RightVector = TankPawn->GetActorRightVector();

	auto ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, Direction)));
	auto RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightVector, Direction)));

	int RotationValue = 0;

	if (ForwardAngle > 5)
	{
		if (ForwardAngle > 45)
			TankPawn->MoveForward(0);
		else
		{
			TankPawn->MoveForward(1);
		}

		if (RightAngle > 90)
			RotationValue = -1;
		else
			RotationValue = 1;
	}

	if (RotationValue != 0)
		TankPawn->RotateRight(RotationValue);
	else
		TankPawn->RotateRight(0);

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TankPawn = Cast<ATankPawn>(InPawn);

	if (!TankPawn)
		return;

	WaypointTag = TankPawn->WaypointTag;

	TArray<AActor*> Actors;
	TArray<AWaypointActor*> Waiponts;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypointActor::StaticClass(), Actors);

	for (auto Actor: Actors)
	{
		auto Waypoint = CastChecked<AWaypointActor>(Actor);
		if (Waypoint->Tags.Contains(WaypointTag))
			Waiponts.Add(Waypoint);
	}

	Waiponts.Sort([] (const AWaypointActor& a, const AWaypointActor& b)
	{
		return a.WaypointIndex > b.WaypointIndex;
	});

	for (auto Waypoint: Waiponts)
	{
		PatrollingPoints.Add(Waypoint->GetActorLocation());
	}
/*
	for (int index = 1; index < PatrollingPoints.Num(); index++)
	{
		DrawDebugLine(GetWorld(), PatrollingPoints[index-1], PatrollingPoints[index], FColor::Green, true);
	}

	DrawDebugLine(GetWorld(), PatrollingPoints[0], PatrollingPoints[PatrollingPoints.Num()-1], FColor::Green, true);
	*/
}

FVector AEnemyAIController::GetShootTarget() const
{
	if (Target.IsValid())
		return Target->GetActorForwardVector();

	if (TankPawn)
		return TankPawn->TurretMesh->GetComponentLocation() + TankPawn->TurretMesh->GetForwardVector();
	
	return FVector::ZeroVector;
}
