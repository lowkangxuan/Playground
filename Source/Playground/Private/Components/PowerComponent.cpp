// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PowerComponent.h"
#include "Components/LightReceivingComponent.h"

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
	SolarPowerComponent = GetOwner()->GetComponentByClass<ULightReceivingComponent>();
	UE_LOG(LogTemp, Log, TEXT("%s"), *SolarPowerComponent->GetName());
	if (SolarPowerComponent != nullptr) { SolarPowerComponent->OnSunlightReceivedDelegate.AddUniqueDynamic(this, &UPowerComponent::Charge); }
}

void UPowerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	SolarPowerComponent->OnSunlightReceivedDelegate.RemoveAll(this);
}


// Called every frame
void UPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerComponent::Charge(float Delta)
{
	if (bIsFullyCharged) return;
	CurrentPower = FMath::Clamp(CurrentPower + (ChargeRate * Delta), 0, MaxCapacity);

	if (CurrentPower == MaxCapacity)
	{
		bIsFullyCharged = true;
		OnFullChargeDelegate.Broadcast();
	}
}

void UPowerComponent::Discharge(float Delta)
{
	if (bIsFullyCharged) { bIsFullyCharged = false; }
	CurrentPower = FMath::Clamp(CurrentPower - (DischargeRate * Delta), 0, 0);
	if (CurrentPower == 0) { OnFullDischargeDelegate.Broadcast(); }
}

