// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualPlayerState.h"
#include "RitualGameState.h"
#include "OgnamCharacter.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

ARitualPlayerState::ARitualPlayerState()
{
	Team = TEXT("Undefined");
	bIsAlive = false;
}

void ARitualPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARitualPlayerState, Team);
}

void ARitualPlayerState::Tick(float DeltaTime)
{
	if (!GetWorld()->GetGameState()->HasMatchStarted())
		return;
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(GetPawn());
	if (Character != nullptr || !Character->IsAlive())
	{
		bIsAlive = Character->IsAlive();
	}
	else
	{
		bIsAlive = false;
	}

}

void ARitualPlayerState::SetTeam(FName name)
{
	Team = name;
}

FName ARitualPlayerState::GetTeam() const
{
	return Team;
}

void ARitualPlayerState::SetTeamIndex(int32 index)
{
	TeamIndex = index;
}

int32 ARitualPlayerState::GetTeamIndex() const
{
	return TeamIndex;
}

void ARitualPlayerState::SetIsAlive(bool Value)
{
	bIsAlive = Value;
}

bool ARitualPlayerState::IsAlive() const
{
	return bIsAlive;
}

FName ARitualPlayerState::GetSide() const
{
	ARitualGameState* GameState = GetWorld()->GetGameState<ARitualGameState>();
	if (GameState == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game state not valid!"));
		return FName();
	}

	if (Team.IsEqual(GameState->GetCurrentOffenseTeam()))
	{
		return GameState->OffenseName;
	}
	else if (Team.IsEqual(GameState->GetCurrentDefenseTeam()))
	{
		return GameState->DefenseName;
	}
	UE_LOG(LogTemp, Warning, TEXT("Team name not valid!"));
	return FName();
}