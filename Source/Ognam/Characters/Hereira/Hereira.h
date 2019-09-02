// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Hereira.generated.h"

/**
 *	A Masked Woman
 */
UCLASS()
class OGNAM_API AHereira : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AHereira();

	/*
	**	Binded Function
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

protected:
	/*
	**	Abilities
	*/
	//Basic
	void FireArrow();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerFireArrow();
	bool ServerFireArrow_Validate() { return true; };
	void ServerFireArrow_Implementation();

	//Mobility
	void StartSprint();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStartSprint();
	bool ServerStartSprint_Validate() { return true; };
	void ServerStartSprint_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void ApplySprint();
	void ApplySprint_Implementation();
	

	void StopSprint();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStopSprint();
	bool ServerStopSprint_Validate() { return true; };
	void ServerStopSprint_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void InterruptSprint();
	void InterruptSprint_Implementation();

	//Unique
	void LoadExplosiveShot();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerLoadExplosiveShot();
	bool ServerLoadExplosiveShot_Validate() { return true; };
	void ServerLoadExplosiveShot_Implementation();

	/*
	**	Props
	*/

	UPROPERTY(VisibleAnywhere, Category = Ability)
	bool bIsExplosiveShot;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle BasicReload;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle SprintCooldown;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle ExplosiveShotCooldown;

	UPROPERTY(VisibleAnywhere, Category = Ability)
	class UHereiraSprint* CurrentSprint;
};