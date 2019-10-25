// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "Hereira.h"
#include "HereiraSprint.h"
#include "HereiraCrossbow.h"
#include "HereiraThrowMolotov.h"
#include "Sound/SoundCue.h"

AHereira::AHereira()
{
	//static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/CharacterHUD/HereiraHUD"));
	//if (HUDFinder.Succeeded())
	//{
	//	CharacterSpecificHUDClass = HUDFinder.Class;
	//}

	//static ConstructorHelpers::FObjectFinder<USoundCue> ShotSound(TEXT("SoundCue'/Game/Sounds/Crossbow/CrossbowShot.CrossbowShot'"));
	//ShotAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ShotAudio"));
	//ShotAudio->SetSound(ShotSound.Object);
	//ShotAudio->SetupAttachment(RootComponent);
	//ShotAudio->SetRelativeLocation(FVector::ZeroVector);
	//ShotAudio->bAutoActivate = 0;
	CharacterName = FText::FromString(TEXT("Hereira"));

	//static ConstructorHelpers::FObjectFinder<USoundCue> WalkingCue(TEXT("SoundCue'/Game/Sounds/Arrow/SparkFizzle_Cue.SparkFizzle_Cue'"));
	//WalkingSoundCue = WalkingCue.Object;
}

void AHereira::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UHereiraCrossbow>(this, TEXT("Weapon"));
	Mobility = NewObject<UHereiraSprint>(this, TEXT("Mobility"));
	Unique = NewObject<UHereiraThrowMolotov>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
