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
	
	RootComponent = RootMesh;
	IndicatorMesh->SetupAttachment(RootMesh);
	IndicatorMesh->SetRenderCustomDepth(true);
	IndicatorUX->SetupAttachment(RootMesh);
}

// Called when the game starts or when spawned
void APhysicalItem::BeginPlay()
{
	Super::BeginPlay();
	RootMesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &APhysicalItem::OnOverlap);
	RootMesh->OnComponentEndOverlap.AddUniqueDynamic(this, &APhysicalItem::OnEndOverlap);
}

void APhysicalItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	RootMesh->OnComponentBeginOverlap.RemoveAll(this);
	RootMesh->OnComponentEndOverlap.RemoveAll(this);
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

void APhysicalItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsOverlapping = true;
}

void APhysicalItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsOverlapping = false;
}

void APhysicalItem::ConstraintPhysics_Implementation()
{
	ICursorInteractionInterface::ConstraintPhysics_Implementation();
	RootMesh->SetPhysicsLinearVelocity(FVector(0));
	RootMesh->SetPhysicsAngularVelocityInDegrees(FVector(0));
}

void APhysicalItem::OnMouseClicked_Implementation()
{
	ICursorInteractionInterface::OnMouseClicked_Implementation();
	bIsPickedUp = true;
	SetHighlight(bIsPickedUp);
	if (bIsPickedUp)
	{
		RootMesh->SetCollisionProfileName("PhysicalItemPicked");
		RootMesh->BodyInstance.bLockZRotation = false;
		OnPickUpDelegate.Broadcast();
	}
}

void APhysicalItem::OnCursorEnter_Implementation()
{
	ICursorInteractionInterface::OnCursorEnter_Implementation();
	SetHighlight(true);
}

void APhysicalItem::OnCursorExit_Implementation()
{
	ICursorInteractionInterface::OnCursorExit_Implementation();
	SetHighlight(false);
}

void APhysicalItem::OnReleased_Implementation()
{
	ICursorInteractionInterface::OnReleased_Implementation();
	bIsPickedUp = false;
	if (bIsOverlapping)
	{
		ConstraintPhysics_Implementation();
		SetActorLocation(GetActorLocation() + FVector(0, 0, 200));
	}
	RootMesh->SetCollisionProfileName("PhysicalItem");
	RootMesh->BodyInstance.bLockZRotation = true;
	OnDropDelegate.Broadcast();
}

