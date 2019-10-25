// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraMolotov.generated.h"

UCLASS()
class OGNAM_API AHereiraMolotov : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:	
	AHereiraMolotov();

	void SetInitialVelocity(FVector Velocity);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void ProjectileStop(const FHitResult& ImpactResult);

	UFUNCTION()
	void OnRep_CharacterVelocity();

	virtual void BeginPlay() override;

	/*
	**	Props
	*/
	UPROPERTY(ReplicatedUsing=OnRep_CharacterVelocity)
	FVector CharacterVelocity;

};
