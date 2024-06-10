// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PhysicalItem.h"


// Sets default values
APhysicalItem::APhysicalItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetCollisionProfileName("PhysicalItem");

	IndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Indicator Mesh");
	IndicatorMesh->SetCollisionProfileName("NoCollision");
	IndicatorMesh->SetVisibility(false);
	IndicatorMesh->SetRenderInMainPass(false);
	IndicatorMesh->SetCastShadow(false);
	IndicatorMesh->SetEnableGravity(false);
	IndicatorMesh->SetComponentTickEnabled(false);
	
	RootComponent = RootMesh;
	IndicatorMesh->SetupAttachment(RootMesh);
	IndicatorMesh->SetRenderCustomDepth(true);
}

// Called when the game starts or when spawned
void APhysicalItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicalItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicalItem::SetPickedup_Implementation(bool bPickedup)
{
	IItemInteractionInterface::SetPickedup_Implementation(bPickedup);
	HighlightItem_Implementation(bPickedup);
	if (bPickedup)
	{
		RootMesh->SetCollisionProfileName("PhysicalItemPicked");
		RootMesh->BodyInstance.bLockZRotation = false;
		OnPickedUpDelegate.Broadcast();
	}
	else
	{
		RootMesh->SetCollisionProfileName("PhysicalItem");
		RootMesh->BodyInstance.bLockZRotation = true;
		OnDroppedDelegate.Broadcast();
	}
}

void APhysicalItem::ConstraintPhysics_Implementation()
{
	IItemInteractionInterface::ConstraintPhysics_Implementation();
	RootMesh->SetPhysicsLinearVelocity(FVector(0));
	RootMesh->SetPhysicsAngularVelocityInDegrees(FVector(0));
}

void APhysicalItem::HighlightItem_Implementation(bool bHighlight)
{
	IItemInteractionInterface::HighlightItem_Implementation(bHighlight);
	if (IsValid(IndicatorMesh->GetStaticMesh()) && bHighlight)
	{
		IndicatorMesh->SetVisibility(true);
	}
	else
	{
		IndicatorMesh->SetVisibility(false);
	}
}

