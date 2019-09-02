// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameState.h"
#include "UnrealNetwork.h"
#include "OgnamPlayerState.h"
#include "OgnamCharacter.h"

AOgnamGameState::AOgnamGameState()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AOgnamGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Count number of players on both teams(maybe find a better way)
	int32 ACount = 0;
	int32 BCount = 0;
	for (APlayerState* PlayerState : PlayerArray)
	{
		AOgnamCharacter* OgnamCharacter = Cast<AOgnamCharacter>(PlayerState->GetPawn());
		if (OgnamCharacter != nullptr && OgnamCharacter->IsAlive())
		{
			ACount++;
		}
	}
	TeamBCount = BCount;
	TeamACount = ACount;
}

void AOgnamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamGameState, TeamACount);
	DOREPLIFETIME(AOgnamGameState, TeamBCount);
}

int32 AOgnamGameState::GetTeamACount() const
{
	return TeamACount;
}

int32 AOgnamGameState::GetTeamBCount() const
{
	return TeamBCount;
}