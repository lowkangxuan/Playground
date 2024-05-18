// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlaygroundPlayerController.h"

#include "Items/Pickups/PickupBase.h"
#include "Items/ItemObject.h"

void APlaygroundPlayerController::DropItem(UItemObject* ItemToDrop)
{
	if (ItemToDrop == nullptr) return;

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<APickupBase>(APickupBase::StaticClass(), GetPawn()->GetActorLocation() + (GetPawn()->GetActorForwardVector() * FVector(200, 0, 0)), GetPawn()->GetActorRotation(), SpawnParams);
}
