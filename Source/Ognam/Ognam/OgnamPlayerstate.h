// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OgnamPlayerState.generated.h"

/**
 *	Put things that are common
 */
UCLASS()
class OGNAM_API AOgnamPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AOgnamPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	virtual void OverrideWith(class APlayerState* PlayerState) override;

	virtual void NotifyDamageDealt(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage);
	virtual void NotifyDamageRecieved(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage);
	virtual void NotifyKill(AActor* Causer, AActor* Reciever, AController* KillInstigator, AController* RecieverController);
	virtual void NotifyDeath(AActor* Causer, AActor* Reciever, AController* KillInstigator, AController* RecieverController);

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetTeam(FName name);

	UFUNCTION(BlueprintCallable)
	FName GetTeam() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	void SetIsAlive(bool Value);

	UFUNCTION(BlueprintCallable)
	UClass* GetPawnClass() const;

	UFUNCTION(BlueprintCallable)
	void SetPawnClass(UClass* Pawn);

	UFUNCTION(BlueprintCallable)
	void SetSelectedPawnClass(class UClass* Pawn);

	UFUNCTION(BlueprintCallable)
	UClass* GetSelectedPawnClass() const;

	UFUNCTION(BlueprintCallable)
	bool ShouldHideName() const;

	void SetShouldHideName(bool bHide);

	/* Chat functions */
	UFUNCTION(Netmulticast, Unreliable)
	void NetReceiveMessage(const FString& Message, class APlayerState* Sender);
	void NetReceiveMessage_Implementation(const FString& Message, class APlayerState* Sender);

	UFUNCTION(Server, Unreliable)
	void ServerSendMessage(const FString& Message);
	void ServerSendMessage_Implementation(const FString& Message);

	UFUNCTION(BlueprintCallable)
	void DisplayMessage(const FString& Message, class APlayerState* Sender);

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	FName Team;

	UPROPERTY(Transient, VisibleAnywhere, Replicated, BlueprintReadOnly)
	int32 NumKill;

	UPROPERTY(Transient, VisibleAnywhere, Replicated, BlueprintReadOnly)
	int32 NumDeath;

	UPROPERTY(Transient, VisibleAnywhere, Replicated, BlueprintReadOnly)
	bool bIsAlive;

	UPROPERTY(Transient, VisibleAnywhere, Replicated, BlueprintReadOnly)
	bool bHidePlayerName;

	UPROPERTY(Transient, Replicated)
	UClass* PawnClass;

	UPROPERTY(Transient, Replicated)
	UClass* SelectedPawnClass;
};
