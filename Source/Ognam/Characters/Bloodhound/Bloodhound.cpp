// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloodhound.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
ABloodhound::ABloodhound()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(61.6f);
	GetCapsuleComponent()->SetCapsuleRadius(23.8f);
	GetMesh()->SetRelativeScale3D(FVector(.7f));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -63.f));
}

void ABloodhound::BeginPlay()
{
	Super::BeginPlay();
}