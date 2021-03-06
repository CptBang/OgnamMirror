// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraArrow.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "HereiraBulletImpact.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

// Sets default values
AHereiraArrow::AHereiraArrow()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(40.f, 5.f, 5.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Game/Meshes/Arrow/M_Arrow_Static.M_Arrow_Static'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(0.66, 0.66, .66f));
	Mesh->SetRelativeLocationAndRotation(FVector(-20.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 15000.f;
	Movement->OnProjectileStop.AddDynamic(this, &AHereiraArrow::ProjectileStop);
	Movement->ProjectileGravityScale = 0.f;

	//Stop happens only when two collision is blocking eachother.

	BaseDamage = 60.f;
}

// Called when the game starts or when spawned
void AHereiraArrow::BeginPlay()
{
	Super::BeginPlay();
	Collision->MoveIgnoreActors.Add(GetInstigator());
	GetWorldTimerManager().SetTimer(LifeSpan, this, &AHereiraArrow::EndLifeSpan, 3., false);
}

void AHereiraArrow::ProjectileStop(const FHitResult& ImpactResult)
{
	FVector ImpactLocation = ImpactResult.ImpactPoint;
	NetPlayFeedback_Implementation(ImpactLocation);
	APawn* Reciever = Cast<APawn>(ImpactResult.GetActor());
	IKillable* Killable = Cast<IKillable>(ImpactResult.GetActor());
	if (Killable)
	{
		if (UOgnamStatics::CanDamage(GetWorld(), GetInstigator(), Killable, EDamageMethod::DamagesEnemy))
		{
			OnCharacterHit(Killable, ImpactResult);
			Collision->AttachToComponent(ImpactResult.GetComponent(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), ImpactResult.BoneName);
		}
		else
		{
			Destroy();
		}
	}
}

void AHereiraArrow::NetPlayFeedback_Implementation(FVector ImpactLocation)
{
	AHereiraBulletImpact* Impact = GetWorld()->SpawnActor<AHereiraBulletImpact>(ImpactLocation, FRotator::ZeroRotator);
}

void AHereiraArrow::EndLifeSpan()
{
	Destroy();
}

void AHereiraArrow::OnCharacterHit(APawn* OtherCharacter, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}
	UGameplayStatics::ApplyPointDamage(OtherCharacter, BaseDamage, SweepResult.ImpactNormal, SweepResult, GetInstigatorController(), this, nullptr);
}

void AHereiraArrow::OnCharacterHit(IKillable* Killable, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	AActor* OtherCharacter = Cast<AActor>(Killable);
	if (OtherCharacter)
	{
		UGameplayStatics::ApplyPointDamage(OtherCharacter, BaseDamage, SweepResult.ImpactNormal, SweepResult, GetInstigatorController(), this, nullptr);
	}
}