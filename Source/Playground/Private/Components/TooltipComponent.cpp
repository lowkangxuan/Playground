// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TooltipComponent.h"
#include "Items/ItemDataAsset.h"

// Sets default values for this component's properties
UTooltipComponent::UTooltipComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UTooltipComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTooltipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTooltipComponent::DisplayTooltip(UItemDataAsset* Info)
{
	if (Info == nullptr) return;
	UE_LOG(LogTemp, Log, TEXT("%s"), *Info->DisplayName.ToString());
}

void UTooltipComponent::RemoveTooltip()
{
}

