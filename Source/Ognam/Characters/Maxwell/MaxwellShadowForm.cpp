// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellShadowForm.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"

UMaxwellShadowForm::UMaxwellShadowForm()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced | EStatusEffect::Rooted | EStatusEffect::Unbreakable;
	Duration = .2f;
}

void UMaxwellShadowForm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMaxwellShadowForm, Direction);
}

void UMaxwellShadowForm::TickModifier(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Replicated, Vector: X %f, Y %f, Z %f"), Direction.X, Direction.Y, Direction.Z);
	Target->AddMovementInput(Direction, 1.f, true);
	Target->Acceleration += Target->BaseAcceleration * 2;
	Target->Speed += Target->BaseSpeed * 2;
}

void UMaxwellShadowForm::SetDirection(FVector Vector)
{
	Direction = Vector;
}


