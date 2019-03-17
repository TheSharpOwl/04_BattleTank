// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	/*
	Important Note :
	Casting means converting some type to another similar one (such as putting int in float)
	*/
	if (PlayerTank)
	{
		//Move towards a player tank
		MoveToActor(PlayerTank, AcceptanceRadius);
		//Aim at the player's tank
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire from the controlled tank (get The Controlled Tank)
		//ControlledTank->Fire();
	}
}
