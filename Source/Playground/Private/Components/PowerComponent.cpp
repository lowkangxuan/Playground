// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PowerComponent.h"
#include "Components/LightReceivingComponent.h"
#include "Components/PickableComponent.h"

// Sets default values for this component's properties
UPowerComponent::UPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPowerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(SolarPowerComponent = GetOwner()->GetComponentByClass<ULightReceivingComponent>()))
	{
		SolarPowerComponent->OnSunlightReceivedDelegate.AddUniqueDynamic(this, &UPowerComponent::Charge);
	}

	if (IsValid(OwnerItem = GetOwner()) && IsValid(OwnerItem->GetComponentByClass<UPickableComponent>()))
	{
		OwnerItem->GetComponentByClass<UPickableComponent>()->OnPickUp.AddUniqueDynamic(this, &UPowerComponent::SetDisabled);
		OwnerItem->GetComponentByClass<UPickableComponent>()->OnDrop.AddUniqueDynamic(this, &UPowerComponent::SetEnabled);
	}
}

void UPowerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (IsValid(SolarPowerComponent)) SolarPowerComponent->OnSunlightReceivedDelegate.RemoveAll(this);
	if (IsValid(OwnerItem) && IsValid(OwnerItem->GetComponentByClass<UPickableComponent>()))
	{
		OwnerItem->GetComponentByClass<UPickableComponent>()->OnPickUp.RemoveAll(this);
		OwnerItem->GetComponentByClass<UPickableComponent>()->OnDrop.RemoveAll(this);
	}
}


// Called every frame
void UPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerComponent::Charge(float Delta)
{
	if (bIsFullyCharged || !bEnabled) return;
	CurrentPower = FMath::Clamp(CurrentPower + (ChargeRate * Delta), 0, MaxCapacity);

	if (CurrentPower == MaxCapacity)
	{
		bIsFullyCharged = true;
		OnFullCharge.Broadcast();
	}
}

void UPowerComponent::Discharge(float Delta)
{
	if (bIsFullyCharged) { bIsFullyCharged = false; }
	CurrentPower = FMath::Clamp(CurrentPower - (DischargeRate * Delta), 0, 0);
	if (CurrentPower == 0) { OnFullDischarge.Broadcast(); }
}

void UPowerComponent::SetEnabled()
{
	bEnabled = true;
}

void UPowerComponent::SetDisabled()
{
	bEnabled = false;
}

