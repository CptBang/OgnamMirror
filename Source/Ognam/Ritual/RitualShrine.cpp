// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "RitualShrine.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "RitualPlayerState.h"
#include "Ognam/OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"

// Sets default values
ARitualShrine::ARitualShrine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetStaticMesh(Mesh.Object);
	StaticMesh->SetMobility(EComponentMobility::Static);
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	StaticMesh->SetWorldScale3D(FVector(1, 1, 5));
	StaticMesh->SetupAttachment(RootComponent);

	RootComponent = StaticMesh;

	CaptureField = CreateDefaultSubobject<UBoxComponent>(TEXT("Capture Point"));
	CaptureField->SetupAttachment(RootComponent);
	CaptureField->SetRelativeLocation(FVector::ZeroVector);
	CaptureField->SetCollisionProfileName(TEXT("Trigger"));
	CaptureField->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	CaptureField->bHiddenInGame = false;
	CaptureField->OnComponentBeginOverlap.AddDynamic(this, &ARitualShrine::OnEnterField);
	CaptureField->OnComponentEndOverlap.AddDynamic(this, &ARitualShrine::OnExitField);

	//bReplicates = true;

	CaptureDuration = 20.f;
	SpeedMultiplier = .15f;

	ShrineName = FText::FromString("Default");
}

void ARitualShrine::BeginPlay()
{
	Super::BeginPlay();
	CaptureProgress = 0.f;
}

void ARitualShrine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AttackerCount > DefenderCount)
	{
		CaptureProgress += DeltaTime + (AttackerCount - DefenderCount - 1) * DeltaTime * SpeedMultiplier;
	}
	else
	{
		CaptureProgress = 0;
	}
}

void ARitualShrine::Reset()
{
	Super::Reset();

	NetReset();
	O_LOG(TEXT("Shrine Reset"));
}

void ARitualShrine::NetReset_Implementation()
{
	AttackerCount = 0;
	DefenderCount = 0;
	CaptureProgress = 0;
}

void ARitualShrine::OnEnterField(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);

	if (!Character)
		return;

	ARitualPlayerState* PlayerState = Character->GetPlayerState<ARitualPlayerState>();

	if (!PlayerState)
		return;

	if (PlayerState->GetSide() == TEXT("Offense"))
		AttackerCount++;
	if (PlayerState->GetSide() == TEXT("Defense"))
		DefenderCount++;
}

void ARitualShrine::OnExitField(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);

	if (!Character)
		return;

	ARitualPlayerState* PlayerState = Character->GetPlayerState<ARitualPlayerState>();

	if (!PlayerState)
		return;

	if (PlayerState->GetSide() == TEXT("Offense"))
		AttackerCount--;
	if (PlayerState->GetSide() == TEXT("Defense"))
		DefenderCount--;
}

bool ARitualShrine::ShouldRoundEnd() const
{
	return (CaptureProgress >= CaptureDuration);
}

bool ARitualShrine::IsBeingCaptured() const
{
	return GetProgressPercent() > 0 || AttackerCount > DefenderCount;
}

float ARitualShrine::GetProgressPercent() const
{
	return CaptureProgress / CaptureDuration;
}

