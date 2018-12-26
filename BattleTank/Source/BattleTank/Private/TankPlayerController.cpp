// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	/*
	auto ControlledTank = GetControllerTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerBeginPlay"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error Sorry!"));
	}
	*/
	
}
ATank* ATankPlayerController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}
