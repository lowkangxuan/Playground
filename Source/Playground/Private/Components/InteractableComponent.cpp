// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"
#include "Items/ItemDataAsset.h"
#include "Components/TooltipComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	TooltipComponent = GetOwner()->GetComponentByClass<UTooltipComponent>();
}

void UInteractableComponent::ProcessCursorEnter()
{
	if (bIsHovered) return;
	bIsHovered = true;
	TooltipComponent->ToggleTooltip(InteractionData, InteractionDelay);
	OnCursorEnter.Broadcast();
}

void UInteractableComponent::ProcessCursorExit()
{
	if (bIsHovered)
	{
		bIsHovered = false;
		TooltipComponent->RemoveTooltip();
		OnCursorExit.Broadcast();
	}
}

void UInteractableComponent::ProcessMouseClick()
{
	bIsHovered = false;
	TooltipComponent->RemoveTooltip();
	OnMouseClick.Broadcast();
}

void UInteractableComponent::ProcessInput()
{
	OnInteractSuccess.Broadcast();
	OnInteractCancelled.Broadcast();
}

void UInteractableComponent::SetInteractionData(UItemDataAsset* Data)
{
	if (Data) InteractionData = Data;
}

