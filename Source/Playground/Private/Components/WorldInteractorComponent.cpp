// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WorldInteractorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


UWorldInteractorComponent::UWorldInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CursorDecal = CreateDefaultSubobject<UDecalComponent>("Cursor Decal");
	//CursorDecal->RegisterComponent();
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
	
	CursorDecal->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CursorDecal->SetMaterial(0, DecalMat);
	CursorDecal->SetRelativeRotation(FRotator(90, 0, 0));
	CursorDecal->DecalSize = FVector(16, 16, 16);
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

	CursorDecal->SetWorldLocation(RayEndLocation);
	if (HitActor) CursorDecal->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(OutResult.ImpactNormal));
	if (HitComp && HitComp->GetAttachParent()) UE_LOG(LogTemp, Log, TEXT("%s: %s"), *HitComp->GetAttachParent()->GetName(), HitComp->Implements<UInteractionInterface>() ? TEXT("true"): TEXT("false"));
	if (HitActor) UE_LOG(LogTemp, Log, TEXT("%s: %s"), *HitActor->GetName(), HitActor->Implements<UInteractionInterface>() ? TEXT("true"): TEXT("false"));

	if (bIsGrabbingItem)
	{
		SetCursorVisibility(true);
		PhysicsHandleComponent->SetTargetLocation(RayEndLocation + FVector(0, 0, 150));
		return;
	}

	if (IsHitValidComponent(HitComp))
	{
		HoveredComp = HitComp;
		IInteractionInterface::Execute_OnCursorEnter(HoveredComp->GetAttachParent());
		SetCursorVisibility(false);
	}
	else
	{
		if (HoveredComp)
		{
			IInteractionInterface::Execute_OnCursorExit(HoveredComp->GetAttachParent());
		}
		HoveredComp = nullptr;
		SetCursorVisibility(true);
	}
	
	bCanGrabActor = HitActor && HitActor->Implements<UInteractionInterface>();
	if (bCanGrabActor)
	{
		// Turn off highlight when changing target actor 
		if (HoveredActor && HoveredActor != HitActor) IInteractionInterface::Execute_OnCursorExit(HoveredActor);
		HoveredActor = HitActor;
		IInteractionInterface::Execute_OnCursorEnter(HoveredActor);
		SetCursorVisibility(false);
	}
	else if (HoveredActor)
	{
		IInteractionInterface::Execute_OnCursorExit(HoveredActor);
		HoveredActor = nullptr;
		SetCursorVisibility(true);
	}
}

void UWorldInteractorComponent::AttemptInteraction()
{
	if (HoveredComp && HoveredComp->GetAttachParent()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		IInteractionInterface::Execute_OnMouseClicked(HoveredComp->GetAttachParent());
		return;
	}
	
	if (bCanGrabActor) // To grab item
	{
		GrabbedActor = HoveredActor;
		bIsGrabbingItem = true;
		bCanGrabActor = false;
		IInteractionInterface::Execute_OnMouseClicked(GrabbedActor);
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(Cast<UPrimitiveComponent>(GrabbedActor->GetRootComponent()), NAME_None, GrabbedActor->GetActorLocation(), GrabbedActor->GetActorRotation());
		PhysicsHandleComponent->SetTargetRotation(FRotator(0, FMath::RoundHalfToEven(GrabbedActor->GetActorRotation().Yaw /90) * 90, 0));
		return;
	}
	
	if (bIsGrabbingItem) // To release item
	{
		bIsGrabbingItem = false;
		PhysicsHandleComponent->ReleaseComponent();
		IInteractionInterface::Execute_OnReleased(GrabbedActor);
		IInteractionInterface::Execute_ConstraintPhysics(GrabbedActor);
		GrabbedActor = nullptr;
		return;
	}
}

bool UWorldInteractorComponent::IsHitValidComponent(const UPrimitiveComponent* HitComponent)
{
	return HitComponent && HitComponent->GetAttachParent() && HitComponent->GetAttachParent()->Implements<UInteractionInterface>();
}

void UWorldInteractorComponent::SetCursorVisibility(bool bVisibility)
{
	CursorDecal->SetVisibility(bVisibility);
}

