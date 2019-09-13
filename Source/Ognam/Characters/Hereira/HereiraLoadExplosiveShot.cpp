// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraLoadExplosiveShot.h"
#include "Ognam/OgnamCharacter.h"
#include "HereiraExplosiveShotReady.h"
#include "TimerManager.h"

UHereiraLoadExplosiveShot::UHereiraLoadExplosiveShot()
{
	AbilityType = EAbilityType::Unique;
}

bool UHereiraLoadExplosiveShot::ShouldShowNumber() const
{
	return Target->GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown);
}

float UHereiraLoadExplosiveShot::GetNumber() const
{
	return Target->GetWorldTimerManager().GetTimerRemaining(ExplosiveShotCooldown);
}


void UHereiraLoadExplosiveShot::FiredExplosiveShot()
{
	ClientFiredExplosiveShot();
}

void UHereiraLoadExplosiveShot::OnButtonPressed()
{
	if (Target->GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown) ||
		Target->GetModifier<UHereiraExplosiveShotReady>() != nullptr)
	{
		return;
	}
	ServerLoadExplosiveShot();
}

void UHereiraLoadExplosiveShot::ServerLoadExplosiveShot_Implementation()
{
	if (Target->GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown) ||
		Target->GetModifier<UHereiraExplosiveShotReady>() != nullptr)
	{
		//UE_LOG(LogNet, Warning, TEXT("%s Mismatch!"), __FUNCTIONW__);
		return;
	}
	UHereiraExplosiveShotReady* ExplosiveShot = NewObject<UHereiraExplosiveShotReady>(Target);
	ExplosiveShot->SetAbility(this);
	ExplosiveShot->RegisterComponent();
}

void UHereiraLoadExplosiveShot::ClientFiredExplosiveShot_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(ExplosiveShotCooldown, 5.f, false);
}