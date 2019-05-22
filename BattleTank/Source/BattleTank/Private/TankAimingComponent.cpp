// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTime)
	{
		FiringState = EFiringState::Reloading;
	}
	//TODO handle aiming and locked state
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	//added this so no one can fire at the start
	LastFireTime = GetWorld()->GetTimeSeconds();
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret))
	{
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//Caluclate Launch Velocity
	 bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet))
		return;

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret))
		return;

	// Work-out difference between current barrel roation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	//We could've used FPlatformTime::Seconds() but it calculates pause and lag times also....

	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel))
		{
			return;
		}
		if (!ensure(ProjectileBlueprint))
		{
			return;
		}
		//Spawn a projectile at the socket location of the barrel
		FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}


