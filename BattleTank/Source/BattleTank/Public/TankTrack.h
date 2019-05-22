// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrank is used to set maximum driving force, and apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	UTankTrack();

private:
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.f;//40 millions! too much

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
