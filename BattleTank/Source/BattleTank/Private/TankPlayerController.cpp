// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
	}

	FoundAimingComponent(AimingComponent);
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
		return;

	FVector HitLocation;// Out parameter
	if (GetSightRayHitLocation(HitLocation))//Has side-effect is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
		//tell controlled tank to aim at this point

}
//Get world location if linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	HitLocation = FVector(1.0);
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;

	if (ensure(GetLookDirection(ScreenLocation, LookDirection)))
	{
		GetLookVectorLocation(LookDirection, HitLocation);
	}
	//Line-trace along that LookDirection, and see what we hit (up to max range)
	return true;
}

bool ATankPlayerController::GetLookVectorLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (ensure(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		))
	{
		HitLocation = HitResult.Location;	
		return true;
	}
	HitLocation = FVector(0.f);
	return false;//Line Trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}


