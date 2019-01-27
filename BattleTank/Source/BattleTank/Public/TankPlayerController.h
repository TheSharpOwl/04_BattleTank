// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last included

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public :

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;

	private:

		UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

		UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333f;

		UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.f;

		ATank* GetControllerTank() const;
		
		void AimTowardsCrosshair();

		bool GetSightRayHitLocation(FVector& HitLocation) const;

		bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

		bool GetLookVectorLocation(FVector LookDirection, FVector &HitLocation) const;
};
