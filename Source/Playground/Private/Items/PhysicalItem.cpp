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

	PickableComponent->SetItemData(ItemComponent->ItemData);
	
	PickableComponent->OnPickUp.AddUniqueDynamic(this, &APhysicalItem::OnItemPickUp);
	PickableComponent->OnCursorEnter.AddUniqueDynamic(this, &APhysicalItem::OnCursorEnter);
	PickableComponent->OnDrop.AddUniqueDynamic(this, &APhysicalItem::OnItemDrop);
	PickableComponent->OnCursorExit.AddUniqueDynamic(this, &APhysicalItem::OnCursorExit);
}

void APhysicalItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	PickableComponent->OnPickUp.RemoveAll(this);
	PickableComponent->OnCursorEnter.RemoveAll(this);
	PickableComponent->OnDrop.RemoveAll(this);
	PickableComponent->OnCursorExit.RemoveAll(this);
}

// Called every frame
void APhysicalItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicalItem::OnCursorEnter()
{
	EnableHighlight();
}

void APhysicalItem::OnCursorExit()
{
	DisableHighlight();
}

void APhysicalItem::OnItemPickUp()
{
	EnableHighlight();
}

void APhysicalItem::OnItemDrop()
{
	DisableHighlight();
}

void APhysicalItem::EnableHighlight()
{
	IndicatorUX->ActivateIndicator(true);
	if (IsValid(IndicatorMesh->GetStaticMesh())) IndicatorMesh->SetVisibility(true);
}

void APhysicalItem::DisableHighlight()
{
	IndicatorUX->ActivateIndicator(false);
	if (IsValid(IndicatorMesh->GetStaticMesh())) IndicatorMesh->SetVisibility(false);
}
