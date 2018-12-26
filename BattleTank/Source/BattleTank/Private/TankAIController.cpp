// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	auto PossesedTank = GetAIControllerTank();
	if (PossesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("this is %s"), *PossesedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("sorry doesn't work!"));
	}
}

ATank *ATankAIController::GetAIControllerTank() const
{
	return Cast<ATank>(GetPawn());
}
