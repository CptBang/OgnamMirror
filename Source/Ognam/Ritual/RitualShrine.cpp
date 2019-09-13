// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualShrine.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "RitualPlayerState.h"
#include "Ognam/OgnamCharacter.h"
#include "RitualAcolyte.h"
#include "UnrealNetwork.h"

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
	CaptureField->bHiddenInGame = false;
	CaptureField->OnComponentBeginOverlap.AddDynamic(this, &ARitualShrine::OnEnterField);
	CaptureField->OnComponentEndOverlap.AddDynamic(this, &ARitualShrine::OnExitField);

	bReplicates = true;

	CaptureDuration = 5.f;
	SpeedMultiplier = .15f;
}

void ARitualShrine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARitualShrine, CaptureProgress);
}

void ARitualShrine::BeginPlay()
{
	Super::BeginPlay();
	CaptureProgress = 0.f;
}


void ARitualShrine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Atk: %d, Def %d"), AttackerCount, DefenderCount);

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

	AttackerCount = 0;
	DefenderCount = 0;
	CaptureProgress = 0;
	UE_LOG(LogTemp, Warning, TEXT("Shrine Reset"));
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
	//UE_LOG(LogTemp, Warning, TEXT("Prog %f, Dur %f"), CaptureProgress, CaptureDuration);
	return (CaptureProgress >= CaptureDuration);
}

float ARitualShrine::GetProgressPercent()
{
	return CaptureProgress / CaptureDuration;
}

