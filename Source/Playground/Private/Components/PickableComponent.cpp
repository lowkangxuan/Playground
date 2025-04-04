// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PickableComponent.h"


// Sets default values for this component's properties
UPickableComponent::UPickableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPickableComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	
}

void UPickableComponent::ProcessMouseClick()
{
	Super::ProcessMouseClick();

	if (bCanBePicked)
	{
		bIsPickedUp = !bIsPickedUp;
		if (bIsPickedUp)
		{
			OwnerRoot->SetCollisionProfileName("PhysicalItemPicked");
			OwnerRoot->BodyInstance.bLockZRotation = true;
			OnPickUp.Broadcast();
		}
		else
		{
			TArray<UPrimitiveComponent*> OverlappingComponents;                     
			TArray<AActor*> OverlappingActors;                                      
			GetOwner()->GetOverlappingComponents(OverlappingComponents);                        
			GetOwner()->GetOverlappingActors(OverlappingActors);                                
                                                                        
			if (OverlappingActors.Num() > 0 || OverlappingComponents.Num() > 0)     
			{                                                                       
				GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0, 0, 200), false, nullptr, ETeleportType::ResetPhysics);          
			}
			ConstraintPhysics();
			OwnerRoot->SetCollisionProfileName("PhysicalItem");                      
			OwnerRoot->BodyInstance.bLockZRotation = true;
			OnDrop.Broadcast();
		}
	}
}

void UPickableComponent::ConstraintPhysics() const
{
	OwnerRoot->SetPhysicsLinearVelocity(FVector(0));
	OwnerRoot->SetPhysicsAngularVelocityInDegrees(FVector(0));
}

