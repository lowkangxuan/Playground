// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PhysicalItem.h"

#include "Components/InteractIndicator.h"


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

	IndicatorUX = CreateDefaultSubobject<UInteractIndicator>("Indicator UX");

	PickableComponent = CreateDefaultSubobject<UPickableComponent>("Pickable Component");
	AddOwnedComponent(PickableComponent);

	ItemComponent = CreateDefaultSubobject<UItemComponent>("Item Component");
	AddOwnedComponent(ItemComponent);
	
	RootComponent = RootMesh;
	IndicatorMesh->SetupAttachment(RootMesh);
	IndicatorMesh->SetRenderCustomDepth(true);
	IndicatorUX->SetupAttachment(RootMesh);
}

// Called when the game starts or when spawned
void APhysicalItem::BeginPlay()
{
	Super::BeginPlay();
}

void APhysicalItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APhysicalItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicalItem::SetHighlight(bool bHighlight)
{
	IndicatorUX->ActivateIndicator(bHighlight);
	if (IsValid(IndicatorMesh->GetStaticMesh())) IndicatorMesh->SetVisibility(bHighlight);
}

void APhysicalItem::ConstraintPhysics_Implementation()
{
	IInteractionInterface::ConstraintPhysics_Implementation();
	RootMesh->SetPhysicsLinearVelocity(FVector(0));
	RootMesh->SetPhysicsAngularVelocityInDegrees(FVector(0));
}

void APhysicalItem::OnMouseClicked_Implementation()
{
	IInteractionInterface::OnMouseClicked_Implementation();
	PickableComponent->OnPickUp();
}

void APhysicalItem::OnReleased_Implementation()
{
	IInteractionInterface::OnReleased_Implementation();
	PickableComponent->OnRelease();
}

void APhysicalItem::OnCursorEnter_Implementation()
{
	IInteractionInterface::OnCursorEnter_Implementation();
	SetHighlight(true);
}

void APhysicalItem::OnCursorExit_Implementation()
{
	IInteractionInterface::OnCursorExit_Implementation();
	SetHighlight(false);
}
