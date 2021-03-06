// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraCrossbow.h"
#include "HereiraCrossbowAction.h"
#include "HereiraCrossbowAimDown.h"

UHereiraCrossbow::UHereiraCrossbow()
{
	MaxAmmo = 4;
	Ammo = MaxAmmo;
	ReloadTime = 1.5f;
	WeaponActionClass = UHereiraCrossbowAction::StaticClass();

	bBindSub = true;
	bCanAimDown = true;
	AimDownClass = UHereiraCrossbowAimDown::StaticClass();
}

void UHereiraCrossbow::StatusEffectApplied(EStatusEffect StatusEffect)
{
}

void UHereiraCrossbow::ActionTaken(EActionNotifier ActionType)
{
	// Reloading cancelling system.
	if (bReloading)
	{
		if ((ActionType & EActionNotifier::Focus) != EActionNotifier::None)
		{
			InterruptReloading();
		}
	}
}
