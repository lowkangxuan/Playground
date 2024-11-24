// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PickableComponent.h"


// Sets default values for this component's properties
UPickableComponent::UPickableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickableComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	
}


// Called every frame
void UPickableComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickableComponent::OnPickUp_Implementation()
{
	OwnerRoot->SetCollisionProfileName("PhysicalItemPicked");
	OwnerRoot->BodyInstance.bLockZRotation = true;
	OnPickUpDelegate.Broadcast();
}

void UPickableComponent::OnRelease_Implementation()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;                     
	TArray<AActor*> OverlappingActors;                                      
	GetOwner()->GetOverlappingComponents(OverlappingComponents);                        
	GetOwner()->GetOverlappingActors(OverlappingActors);                                
                                                                        
	if (OverlappingActors.Num() > 0 || OverlappingComponents.Num() > 0)     
	{                                                                       
		ConstraintPhysics_Implementation();                                 
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0, 0, 200));          
	}                                                                       
	OwnerRoot->SetCollisionProfileName("PhysicalItem");                      
	OwnerRoot->BodyInstance.bLockZRotation = true;
	OnDropDelegate.Broadcast();
}

void UPickableComponent::OnHoverEnter_Implementation()
{
	OnHoverEnterDelegate.Broadcast();
}

void UPickableComponent::OnHoverExit_Implementation()
{
	OnHoverExitDelegate.Broadcast();
}

void UPickableComponent::ConstraintPhysic()
{
	OwnerRoot->SetPhysicsLinearVelocity(FVector(0));
	OwnerRoot->SetPhysicsAngularVelocityInDegrees(FVector(0));
}

void UPickableComponent::ConstraintPhysics_Implementation()
{
	IInteractionInterface::ConstraintPhysics_Implementation();
}

void UPickableComponent::OnMouseClicked_Implementation()
{
	IInteractionInterface::OnMouseClicked_Implementation();
}

void UPickableComponent::OnCursorEnter_Implementation()
{
	IInteractionInterface::OnCursorEnter_Implementation();
}

void UPickableComponent::OnCursorExit_Implementation()
{
	IInteractionInterface::OnCursorExit_Implementation();
}

void UPickableComponent::OnReleased_Implementation()
{
	IInteractionInterface::OnReleased_Implementation();
}

