// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"
#include "Components/ItemComponent.h"

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
	const UItemComponent* ItemComp = GetOwner()->GetComponentByClass<UItemComponent>();
	ensureAlwaysMsgf(ItemComp, TEXT("%s has no ItemComponent present!"), *GetOwner()->GetName());
	ensureAlwaysMsgf(ItemComp->ItemData, TEXT("The ItemComponent in %s has an empty ItemData field!"), *GetOwner()->GetName());
	InteractionData = ItemComp->ItemData;
}

void UInteractableComponent::ProcessCursorEnter()
{
	if (bIsHovered) return;
	bIsHovered = true;
	OnCursorEnter.Broadcast();
	//OnCursorEnterInfo.Broadcast(ItemData);
}

void UInteractableComponent::ProcessCursorExit()
{
	if (bIsHovered) OnCursorExit.Broadcast();
	bIsHovered = false;
}

void UInteractableComponent::ProcessMouseClick()
{
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

