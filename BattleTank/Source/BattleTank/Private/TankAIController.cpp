// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	auto PossesedPlayer = GetPlayerTank();
	if (PossesedPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("this is %s"), *PossesedPlayer->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("sorry doesn't work!"));
	}
}

ATank *ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	
	return Cast<ATank>(PlayerPawn);
}
