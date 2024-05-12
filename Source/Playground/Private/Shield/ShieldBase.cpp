// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield/ShieldBase.h"

AShieldBase::AShieldBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShieldBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false); // Disable Tick first
	CachedShieldHealth = ShieldHealth;
	CachedShieldDowntime = ShieldDowntime;
	
	// We want to "hide" the shield
	if (!bShowShieldOnStart)
	{
		SetActorScale3D(FVector::Zero());
	}
}

void AShieldBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AShieldBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Shield cannot be activated when destroyed
	if (!bIsShieldDestroyed)
	{
		const FVector NewScale = FVector(FMath::VInterpConstantTo(GetActorScale3D(), bIsShieldActivated ? FVector::One() : FVector::Zero(), DeltaTime, 2.0/ActivationTime));
		SetActorScale3D(NewScale);
	}
}

void AShieldBase::TakeDamge_Implementation(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	IShieldInterface::TakeDamge_Implementation(Damage, DamageEvent, EventInstigator, DamageCauser);

	ShieldHealth -= Damage;

	if (ShieldHealth <= 0)
	{
		DestroyShield_Implementation();
	}
}

void AShieldBase::ActivateShield()
{
	bIsShieldActivated = true;
	SetActorTickEnabled(true);
}

void AShieldBase::DeactivateShield()
{
	bIsShieldActivated = false;
	SetActorTickEnabled(true);
}

void AShieldBase::DestroyShield_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Shield Destroyed!"));
	bIsShieldDestroyed = true;
	SetActorScale3D(FVector::Zero()); // Hide the shield
	GetWorld()->GetTimerManager().SetTimer(ShieldDowntimeTimerHandle, this, &AShieldBase::ShieldDowntimeCounter, 1, false, ShieldDowntime);
}

void AShieldBase::ShieldDowntimeCounter()
{
	bIsShieldDestroyed = false;
	ShieldHealth = 100;
}
