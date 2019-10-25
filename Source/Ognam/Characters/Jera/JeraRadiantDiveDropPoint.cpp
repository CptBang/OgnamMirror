// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "JeraRadiantDiveDropPoint.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Ognam/OgnamMacro.h"

// Sets default values
AJeraRadiantDiveDropPoint::AJeraRadiantDiveDropPoint()
{
	InitialLifeSpan = 3.f;
	PlaceHolder = CreateDefaultSubobject<USphereComponent>(TEXT("Place Holder"));
	PlaceHolder->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//PlaceHolder->bHiddenInGame = false;
	RootComponent = PlaceHolder;
}

void AJeraRadiantDiveDropPoint::BeginPlay()
{
	Super::BeginPlay();
	if (!Instigator)
	{
		O_LOG(TEXT("No Instigator"));
		return;
	}
	AOgnamPlayerState* PlayerState = Instigator->GetPlayerState<AOgnamPlayerState>();
	if (!PlayerState)
	{

		O_LOG(TEXT("No player state"));
		return;
	}

	//Test Overlaps.
	TArray<FOverlapResult> Overlaps;
	FCollisionShape Shape;
	Shape.SetSphere(300.f);
	GetWorld()->OverlapMultiByObjectType(Overlaps, GetActorLocation(), FQuat(), ECollisionChannel::ECC_Pawn, Shape);
	for (FOverlapResult& Result : Overlaps)
	{
		AOgnamCharacter* Character = Cast<AOgnamCharacter>(Result.Actor);
		if (!Character)
		{
			continue;
		}
		AOgnamPlayerState* OverlappedPlayerState = Character->GetPlayerState<AOgnamPlayerState>();
		//if not on same team, push them up and deal damage
		if ((!OverlappedPlayerState || OverlappedPlayerState->GetTeam() != PlayerState->GetTeam()) && !Affected.Contains(Character))
		{
			UGameplayStatics::ApplyDamage(Character, 50.f, Instigator->GetController(), this, nullptr);
			if (Character->GetMesh()->IsSimulatingPhysics())
			{
				Character->GetMesh()->AddImpulse(FVector::UpVector * 50000.f);
			}
			else if (HasAuthority())
			{
				Character->GetCharacterMovement()->AddImpulse(FVector::UpVector * 100000.f);
			}
			Affected.Add(Character);
		}
	}
}
