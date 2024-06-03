// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBars/RingedPowerBarIndicator.h"
#include "ComponentUtils.h"
#include "Components/LightReceivingComponent.h"


// Sets default values
ARingedPowerBarIndicator::ARingedPowerBarIndicator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARingedPowerBarIndicator::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(RootComponent->GetAttachParentActor()))
	{
		AActor* OwnerActor = ComponentUtils::GetAttachedParent(RootComponent)->GetOwner();
		ULightReceivingComponent* LightReceivingComponent = OwnerActor->GetComponentByClass<ULightReceivingComponent>();
		
		if (IsValid(OwnerActor) && IsValid(LightReceivingComponent))
		{
			LightReceivingComponent->OnSunlightReceivedDelegate.AddUniqueDynamic(this, &ARingedPowerBarIndicator::Active);
			LightReceivingComponent->OnSunlightBlockedDelegate.AddUniqueDynamic(this, &ARingedPowerBarIndicator::Inactive);
		}
	}
}

// Called every frame
void ARingedPowerBarIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARingedPowerBarIndicator::Active(float Delta)
{
	Super::Active(Delta);
	RingMeshes->SetMaterial(0, SourceMat);
}

void ARingedPowerBarIndicator::Inactive()
{
	Super::Inactive();
	RingMeshes->SetMaterial(0, InactiveMat);
}

