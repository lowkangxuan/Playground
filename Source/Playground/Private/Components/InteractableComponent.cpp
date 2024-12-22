// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"
#include "Items/ItemDataAsset.h"
#include "Components/TooltipComponent.h"
#include "Subsystems/TooltipSubsystem.h"

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
	if (const UGameInstance* GI = GetWorld()->GetGameInstance()) TooltipSubsystem = GI->GetSubsystem<UTooltipSubsystem>();
	//TooltipComponent = GetOwner()->GetComponentByClass<UTooltipComponent>();
}

void UInteractableComponent::ProcessCursorEnter()
{
	if (bIsHovered) return;
	bIsHovered = true;
	ToggleTooltipState(true);
	OnCursorEnter.Broadcast();
}

void UInteractableComponent::ProcessCursorExit()
{
	if (bIsHovered)
	{
		bIsHovered = false;
		ToggleTooltipState(false);
		OnCursorExit.Broadcast();
	}
}

void UInteractableComponent::ProcessMouseClick()
{
	bIsHovered = false;
	ToggleTooltipState(false);
	OnMouseClick.Broadcast();
}

void UInteractableComponent::ProcessInput()
{
	OnInteractSuccess.Broadcast();
	OnInteractCancelled.Broadcast();
}

void UInteractableComponent::SetItemData(UItemDataAsset* Data)
{
	if (Data) ItemData = Data;
}

void UInteractableComponent::ToggleTooltipState(bool bShow)
{
	if (bShow)
	{
		TooltipSubsystem->ShowTooltip(ItemData, GetOwner(), TooltipOffset, InteractionDelay);
	}
	else
	{
		TooltipSubsystem->HideTooltip();
	}
}

