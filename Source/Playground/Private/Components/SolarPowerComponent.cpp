// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SolarPowerComponent.h"

// Sets default values for this component's properties
USolarPowerComponent::USolarPowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USolarPowerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USolarPowerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void USolarPowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

