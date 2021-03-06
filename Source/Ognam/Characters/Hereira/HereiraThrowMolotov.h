// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HereiraThrowMolotov.generated.h"

/**
 *	Potentially make this use actions
 */
UCLASS()
class OGNAM_API UHereiraThrowMolotov : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UHereiraThrowMolotov();

protected:
	//Server Call
	virtual void ActivateAbility() override;
};
