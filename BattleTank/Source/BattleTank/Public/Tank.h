// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;//Forward declaration

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere ,Category = "Setup")
	int32  CurrentHealth = StartingHealth;

public:
	//called by the engine when the damage is being done
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;
};
