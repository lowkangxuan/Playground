// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleBase.h"


// Sets default values
AVehicleBase::AVehicleBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickableComponent = CreateDefaultSubobject<UPickableComponent>(TEXT("PickableComponent"));
	AddOwnedComponent(PickableComponent);

	ItemComponent = CreateDefaultSubobject<UItemComponent>("Item Component");
	AddOwnedComponent(ItemComponent);
}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AVehicleBase::ConstraintPhysics_Implementation()
{
	IInteractionInterface::ConstraintPhysics_Implementation();
}

void AVehicleBase::OnMouseClicked_Implementation()
{
	IInteractionInterface::OnMouseClicked_Implementation();
	PickableComponent->OnPickUp();
}

void AVehicleBase::OnReleased_Implementation()
{
	IInteractionInterface::OnReleased_Implementation();
	PickableComponent->OnRelease();
}

void AVehicleBase::OnCursorEnter_Implementation()
{
	IInteractionInterface::OnCursorEnter_Implementation();
}

void AVehicleBase::OnCursorExit_Implementation()
{
	IInteractionInterface::OnCursorExit_Implementation();
}