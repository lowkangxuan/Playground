// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleBase.h"

#include "EnhancedInputComponent.h"
#include "Components/InteractableComponent.h"

// Sets default values
AVehicleBase::AVehicleBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable Component"));
	AddOwnedComponent(InteractableComponent);

	ItemComponent = CreateDefaultSubobject<UItemComponent>("Item Component");
	AddOwnedComponent(ItemComponent);
}

void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	PC = GetWorld()->GetFirstPlayerController();
	InteractableComponent->SetItemData(ItemComponent->ItemData);
}

void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(InteractAction, ETriggerEvent::Completed, this, &AVehicleBase::DismountPlayer);
	}
}

void AVehicleBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AVehicleBase::UnPossessed()
{
	Super::UnPossessed();
}

void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVehicleBase::DismountPlayer()
{
}

