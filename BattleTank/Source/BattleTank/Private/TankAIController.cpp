// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	/*
	Important Note :
	Casting means converting some type to another similar one (such as putting int in float)
	*/
	if (!ensure(PlayerTank && ControlledTank))
		return;

	//Move towards a player tank
	MoveToActor(PlayerTank, AcceptanceRadius,true,true,true,0,true);//TODO check radis in cm
	//Aim at the player's tank
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire from the controlled tank (get The Controlled Tank)
	//ControlledTank->Fire();
}
