// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeraCrystalSpear.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AJeraCrystalSpear : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:
	AJeraCrystalSpear();

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void ProjectileStop(const FHitResult& ImpactResult);

	float BaseDamage;
};
