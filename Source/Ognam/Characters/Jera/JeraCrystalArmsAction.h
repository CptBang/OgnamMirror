// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "Interfaces/Dispellable.h"
#include "JeraCrystalArmsAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraCrystalArmsAction : public UWeaponActionModifier, public IDispellable
{
	GENERATED_BODY()

public:
	UJeraCrystalArmsAction();

	virtual void BeginPlay() override;

protected:
	virtual void BeginChannel() override;
	virtual void EndChannel() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void StatusEffectApplied(EStatusEffect StatusEffect) override;
	virtual void ActionTaken(EActionNotifier ActionType) override;

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BoxTrigger;

	UPROPERTY(VisibleAnywhere)
	class UMaterial* DamageBoxMaterial;

	UPROPERTY(VisibleAnywhere)
	class UStaticMesh* DamageBoxMesh;

	TSet<AOgnamCharacter*> StrikedCharacters;
};
