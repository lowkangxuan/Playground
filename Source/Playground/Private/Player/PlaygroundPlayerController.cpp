// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlaygroundPlayerController.h"

#include "Components/SphereComponent.h"
#include "Pickups/Public/ItemDrop.h"
#include "Items/ItemObject.h"
#include "Items/ItemDataAsset.h"
#include "Items/Fragments/ItemFragmentSpawner.h"

void APlaygroundPlayerController::DropItem(UItemObject* ItemToDrop)
{
	if (ItemToDrop == nullptr) return;

	FActorSpawnParameters SpawnParams;
	AItemDrop* Pickup = GetWorld()->SpawnActor<AItemDrop>(AItemDrop::StaticClass(), GetPawn()->GetActorLocation() + (GetPawn()->GetActorForwardVector() * FVector(100, 0, 0)), GetPawn()->GetActorRotation(), SpawnParams);
	Pickup->ItemObject = ItemToDrop;
	FVector ForwardVector = Pickup->GetActorForwardVector();

	Pickup->MeshComponent->SetStaticMesh(ItemToDrop->ItemData->GetFragmentByClass<UItemFragmentSpawner>()->Mesh);
	Pickup->CollisionComponent->AddImpulse(ForwardVector * 1000.0f, NAME_None, true);
}
