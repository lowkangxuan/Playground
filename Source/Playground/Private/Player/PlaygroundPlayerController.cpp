// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlaygroundPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "UI/HudManager.h"
#include "Components/SphereComponent.h"
#include "Pickups/Public/ItemDrop.h"
#include "Items/ItemObject.h"
#include "Items/ItemDataAsset.h"
#include "Items/Fragments/ItemFragmentSpawner.h"
#include "Components/WorldInteractorComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "EnhancedInput/Public/InputTriggers.h"

APlaygroundPlayerController::APlaygroundPlayerController()
{
	WorldInteractorComponent = CreateDefaultSubobject<UWorldInteractorComponent>("WorldInteractor");
	AddOwnedComponent(WorldInteractorComponent);

	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	AddOwnedComponent(PhysicsHandleComponent);

	PhysicsHandleComponent->bSoftLinearConstraint = false;
	PhysicsHandleComponent->InterpolationSpeed = 10;
}

void APlaygroundPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlaygroundPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerMappingContext, 1);
		Subsystem->AddMappingContext(UIMappingContext, 1);
		Subsystem->AddMappingContext(EditorMappingContext, 0);
	}
}

void APlaygroundPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// Disable interactor component if possessed pawn is not of type Character
	bool bIsCharacter = InPawn->IsA(ACharacter::StaticClass());
	WorldInteractorComponent->SetComponentTickEnabled(bIsCharacter);
	bShowMouseCursor = bIsCharacter;
	bEnableClickEvents = bIsCharacter;
	bEnableMouseOverEvents = bIsCharacter;
}

void APlaygroundPlayerController::InteractWithWorld()
{
	WorldInteractorComponent->AttemptItemGrabbing();
}

void APlaygroundPlayerController::InteractWithItem(const FInputActionInstance& Instance)
{
	//UInputTrigger* HoldTrigger = NewObject<UInputTrigger>();	
	//const UInputAction* Action = Instance.GetSourceAction();
	//UE_LOG(LogTemp, Log, TEXT("%hs"), Action->Triggers.GetData()->IsA(UInputTrigger::StaticClass()) ? "true" : "false");
	WorldInteractorComponent->TriggerInputInteraction(Instance.GetElapsedTime());
}

void APlaygroundPlayerController::InteractCancelled()
{
	WorldInteractorComponent->InputInteractionCancelled();
}

void APlaygroundPlayerController::RotateHandle(const FInputActionValue& Value)
{
	WorldInteractorComponent->RotateHeldItem(Value.Get<float>());
}

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

AHudManager* APlaygroundPlayerController::GetHudManager()
{
	return Cast<AHudManager>(MyHUD);
}
