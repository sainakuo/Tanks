// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Tanks.h"

#include <string>

#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void ATankPawn::SetupCannon(const TSubclassOf<ACannon>& CannonClass)
{
	if (Cannon)
	{
		
		Cannon->Destroy();
			
		Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, CannonPosition->GetComponentTransform());


		if (Cannon->Type == ECannonType::FireProjectile)
		{
			Cannon->ProjectileCount = ProjectileCount1;
		}
		else
		{
			Cannon->ProjectileCount = ProjectileCount2;
		}
		
		Cannon->AttachToComponent(CannonPosition, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	TankController = Cast<ATankPlayerController>(GetController());

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonType, CannonPosition->GetComponentTransform());
	Cannon->AttachToComponent(CannonPosition, FAttachmentTransformRules::SnapToTargetIncludingScale);

	ProjectileCount1 = Cannon->ProjectileCount;
	ProjectileCount2 = Cannon->ProjectileCount;
	
}

void ATankPawn::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
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
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(TurretMesh->GetComponentLocation(), TankController->GetMouseWorldPosition());
    OldRotation.Yaw = TurretRotation.Yaw;
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretMesh->GetComponentRotation(), OldRotation, TurretAcceleration ));
}

void ATankPawn::Shoot()
{
	if (Cannon)
		Cannon->Shoot();
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
		Cannon->FireSpecial();
}

void ATankPawn::StartFireSeries()
{
	if (Cannon)
		Cannon->StartFireSeries();
}

void ATankPawn::ChangeCannon()
{
	if (Cannon)
	{
		if (Cannon->Type == ECannonType::FireProjectile)
		{
			ProjectileCount1 = Cannon->ProjectileCount;
			SetupCannon(CannonTypeSecond);
			Cannon->ProjectileCount = ProjectileCount2;
		}
		else
		{
			ProjectileCount2 = Cannon->ProjectileCount;
			SetupCannon(CannonType);
			Cannon->ProjectileCount = ProjectileCount1;
		}
	}
}

void ATankPawn::ProjectilePlus(int num)
{
	if (Cannon)
	{
		Cannon->ProjectileCount += num;
	}
}




