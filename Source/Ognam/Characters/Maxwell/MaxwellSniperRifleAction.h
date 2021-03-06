// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "MaxwellSniperRifleAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifleAction : public UWeaponActionModifier
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifleAction();

	virtual void BeginPlay() override;

protected:
	virtual void BeginChannel() override;
	virtual void TickPostDelay(float DeltaTime) override;

	UFUNCTION(NetMulticast, Unreliable)
	void NetPlayFeedback(FVector From, FVector To);
	void NetPlayFeedback_Implementation(FVector From, FVector To);

	/*
	**	Props
	*/
	UPROPERTY()
	class UCurveFloat* DamageCurve;

	UPROPERTY()
	class UParticleSystem* ParticleSystem;

	UPROPERTY()
	class USoundCue* ShotSoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* ShotSound;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ShotTrail;
};
