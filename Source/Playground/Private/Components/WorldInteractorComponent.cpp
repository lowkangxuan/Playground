// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WorldInteractorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/InteractableComponent.h"
#include "Decals/CursorDecal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


UWorldInteractorComponent::UWorldInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CursorDecal = CreateDefaultSubobject<UDecalComponent>("Cursor Decal");
}

void UWorldInteractorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	PhysicsHandleComponent = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComponent)
	{
		// Disable ticking if we can't find a physics handle component from the owner actor; No hope for world interaction
		SetComponentTickEnabled(false);
		return;
	}

	if (CursorClass)
	{
		CursorActor = GetWorld()->SpawnActor<ACursorDecal>(CursorClass, FVector::Zero(), FRotator::ZeroRotator);
	}
}

void UWorldInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	MouseToWorld();
}

void UWorldInteractorComponent::MouseToWorld()
{
	AActor* HitActor;
	UPrimitiveComponent* HitComp;
	FHitResult OutResult;
	FVector RayStart;
	FVector RayDir;
	FCollisionQueryParams RayParams;
	RayParams.AddIgnoredActor(bIsGrabbingItem ? GrabbedActor : nullptr);
	
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(RayStart, RayDir);
	GetWorld()->LineTraceSingleByChannel(OutResult, RayStart, RayStart + (RayDir * 1500), ECC_Visibility, RayParams);
	RayEndLocation = OutResult.bBlockingHit ? OutResult.Location : OutResult.TraceEnd;
	HitActor = OutResult.GetActor();
	HitComp = OutResult.GetComponent();

	CursorActor->SetActorLocation(RayEndLocation);
	if (OutResult.bBlockingHit) CursorActor->SetActorRotation(UKismetMathLibrary::MakeRotFromX(OutResult.ImpactNormal));
	//if (HitActor) UE_LOG(LogTemp, Log, TEXT("%s: %s"), *HitActor->GetName(), HitActor->GetComponentByClass<UInteractableComponent>() ? TEXT("true"): TEXT("false"));

	SetCursorVisibility(!HoveredActor || bIsGrabbingItem);
		
	if (bIsGrabbingItem)
	{
		PhysicsHandleComponent->SetTargetLocation(RayEndLocation + HandleOffset);
		return;
	}
	
	if (IsHitValidActor(HitActor))
	{
		// If there is a previously hovered actor already and we are hovering another valid actor,
		// We want to broadcast the OnCursorExit on the previously hovered actor
		if (HoveredActor && HoveredActor != HitActor)
		{
			HoveredInteractable->ProcessCursorExit();
		}
		HoveredActor = HitActor;
		HoveredInteractable = HoveredActor->GetComponentByClass<UInteractableComponent>();
		HoveredInteractable->ProcessCursorEnter();
		//HoveredInteractable->OnInteractSuccess.AddUniqueDynamic(this, &UWorldInteractorComponent::AttemptItemGrabbing);
	}
	else if (HoveredActor) // If we are moving the cursor to an empty space or invalid actor
	{
		HoveredInteractable->ProcessCursorExit();
		HoveredInteractable = nullptr;
		HoveredActor = nullptr;
	}
}

void UWorldInteractorComponent::AttemptItemGrabbing()
{
	if (bIsGrabbingItem) // To release item
	{
		bIsGrabbingItem = false;
		PhysicsHandleComponent->ReleaseComponent();
		HoveredInteractable->ProcessMouseClick();
		GrabbedActor = nullptr;
		HoveredInteractable = nullptr;
		return;
	}
	
	if (IsHitValidActor(HoveredActor)) // To grab item
	{
		bIsGrabbingItem = true;
		GrabbedActor = HoveredActor;
		HoveredActor = nullptr;
		HoveredInteractable->ProcessMouseClick();
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(Cast<UPrimitiveComponent>(GrabbedActor->GetRootComponent()), NAME_None, GrabbedActor->GetActorLocation(), GrabbedActor->GetActorRotation());
		PhysicsHandleComponent->SetTargetRotation(FRotator(0, FMath::RoundHalfToEven(GrabbedActor->GetActorRotation().Yaw /90) * 90, 0));
	}
}

void UWorldInteractorComponent::TriggerInputInteraction(float ElapsedTime)
{
	if(IsValid(HoveredInteractable) && !bIsGrabbingItem) HoveredInteractable->ProcessInput(ElapsedTime);
}

void UWorldInteractorComponent::InputInteractionCancelled()
{
	if (IsValid(HoveredInteractable))
	{
		HoveredInteractable->InputCancelled();
	}
}

void UWorldInteractorComponent::RotateHeldItem(float InputDelta)
{
	if (!bIsGrabbingItem) return;
	
	FVector ItemLocation;
	FRotator ItemRotation;
	PhysicsHandleComponent->GetTargetLocationAndRotation(ItemLocation, ItemRotation);
	ItemRotation += FRotator(0, InputDelta * 120, 0);
	PhysicsHandleComponent->SetTargetRotation(ItemRotation);
}

bool UWorldInteractorComponent::IsHitValidActor(const AActor* HitActor)
{
	return HitActor && HitActor->GetComponentByClass<UInteractableComponent>();
}

void UWorldInteractorComponent::SetCursorVisibility(bool bVisibility)
{
	CursorActor->SetActorHiddenInGame(!bVisibility);
}

