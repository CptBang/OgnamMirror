// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OgnamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UOgnamGameInstance(const FObjectInitializer& ObjectInitializer);

	//Creates and starts session
	UFUNCTION(BlueprintCallable)
	bool CreateSession(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	//Finds Session
	UFUNCTION(BlueprintCallable)
	void FindSession(bool bIsLAN, bool bIsPresence);

	void CreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void StartSessionComplete(FName SessionName, bool bWasSuccessful);

	void FindSessionComplete(bool bWasSuccessful);
	void JoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FOnCreateSessionCompleteDelegate OnCreateSessionComplete;
	FOnFindSessionsCompleteDelegate OnFindSessionsComplete;
	FOnStartSessionCompleteDelegate OnStartSessionComplete;
	FOnJoinSessionCompleteDelegate OnJoinSessionComplete;

	FDelegateHandle CreateSessionCompleteHandle;
	FDelegateHandle StartSessionCompleteHandle;
	FDelegateHandle FindSessionsCompleteHandle;
	FDelegateHandle JoinSessionCompleteHandle;
};