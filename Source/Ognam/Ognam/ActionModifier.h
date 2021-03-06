// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "ActionModifier.generated.h"

/**
 *	Modifier that is usually for actions that take
 *	Predelay & Postdelay & Channel.
 *	All of these are optional
 */
UCLASS()
class OGNAM_API UActionModifier : public UModifier
{
	GENERATED_BODY()

public:
	UActionModifier();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ShouldEnd() override;
	virtual void TickModifier(float DeltaTime) override;
	EActionStage GetStage() const;

protected:
	virtual void BeginModifier() override;
	virtual void EndModifier() override;

	void ExecutePreDelay();
	virtual void BeginPreDelay();
	virtual void TickPreDelay(float DeltaTime);
	virtual void EndPreDelay();
	void FinishPreDelay();

	void ExecuteChannel();
	virtual void BeginChannel();
	virtual void TickChannel(float DeltaTime);
	virtual void EndChannel();
	void FinishChannel();

	virtual void ExecutePostDelay();
	virtual void BeginPostDelay();
	virtual void TickPostDelay(float DeltaTime);
	virtual void EndPostDelay();
	virtual void FinishPostDelay();

	//ends action before finishing.
	virtual void Interrupt();
	/*
	**	Props
	*/
	EActionStage Stage;

	UPROPERTY(EditAnywhere)
	float PreDelayDuration;

	UPROPERTY(EditAnywhere)
	float ChannelDuration;

	UPROPERTY(EditAnywhere)
	float PostDelayDuration;

	TSet<EStatusEffect> PreDelayStatusEffect;
	TSet<EStatusEffect> ChannelStatusEffect;
	TSet<EStatusEffect> PostDelayStatusEffect;

	EActionNotifier PreDelayAction;
	EActionNotifier ChannelAction;
	EActionNotifier PostDelayAction;

	FTimerHandle PreDelayTimer;
	FTimerHandle ChannelTimer;
	FTimerHandle PostDelayTimer;

	UPROPERTY(Replicated)
	bool bInterrupted;

	float ServerTimeDelay;
};
