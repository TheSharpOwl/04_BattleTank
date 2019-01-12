// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the Barrel the right amount this frame
	//Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation,MinElevationDegress, MaxElevationDegrees);

	//UE_LOG(LogTemp, Warning, TEXT("it's %f"), RawNewElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
