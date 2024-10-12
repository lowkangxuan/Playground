// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WorldInteractorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Interfaces/CursorInteractionInterface.h"
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
	if (HitActor) { CursorDecal->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(OutResult.ImpactNormal)); }

	if (bIsGrabbingItem)
	{
		SetCursorVisibility(true);
		PhysicsHandleComponent->SetTargetLocation(RayEndLocation + FVector(0, 0, 150));
		//PhysicsHandleComponent->GetGrabbedComponent()->SetPhysicsAngularVelocityInDegrees(FVector(0)); // Prevents the grabbed component from rotating out of control
		return;
	}

	if (IsHitValidComponent(HitComp))
	{
		HoveredComp = HitComp;
		ICursorInteractionInterface::Execute_OnCursorEnter(HoveredComp->GetAttachParent());
		SetCursorVisibility(false);
	}
	else
	{
		if (HoveredComp)
		{
			ICursorInteractionInterface::Execute_OnCursorExit(HoveredComp->GetAttachParent());
		}
		HoveredComp = nullptr;
		SetCursorVisibility(true);
	}

	bCanGrabItem = HitActor && HitActor->GetClass()->ImplementsInterface(UCursorInteractionInterface::StaticClass());
	if (bCanGrabItem)
	{
		// Turn off highlight when changing target actor 
		if (HoveredActor && HoveredActor != HitActor) ICursorInteractionInterface::Execute_OnCursorExit(HoveredActor);
		HoveredActor = HitActor;
		ICursorInteractionInterface::Execute_OnCursorEnter(HoveredActor);
		SetCursorVisibility(false);
	}
	else if (HoveredActor)
	{
		ICursorInteractionInterface::Execute_OnCursorExit(HoveredActor);
		HoveredActor = nullptr;
		SetCursorVisibility(true);
	}
}

void UWorldInteractorComponent::AttemptInteraction()
{
	if (IsValid(HoveredComp) && HoveredComp->GetAttachParent()->GetClass()->ImplementsInterface(UCursorInteractionInterface::StaticClass()))
	{
		ICursorInteractionInterface::Execute_OnMouseClicked(HoveredComp->GetAttachParent());
		return;
	}
	
	//if (IsValid(HoveredActor)) ICursorInteractionInterface::Execute_OnMouseClicked(HoveredActor);
	if (bCanGrabItem) // To grab item
	{
		GrabbedActor = HoveredActor;
		bIsGrabbingItem = true;
		bCanGrabItem = false;
		ICursorInteractionInterface::Execute_OnMouseClicked(GrabbedActor);
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(Cast<UPrimitiveComponent>(GrabbedActor->GetRootComponent()), NAME_None, GrabbedActor->GetActorLocation(), GrabbedActor->GetActorRotation());
		PhysicsHandleComponent->SetTargetRotation(FRotator(0, FMath::RoundHalfToEven(GrabbedActor->GetActorRotation().Yaw /90) * 90, 0));
	}
	else if (bIsGrabbingItem) // To release item
	{
		bIsGrabbingItem = false;
		PhysicsHandleComponent->ReleaseComponent();
		ICursorInteractionInterface::Execute_OnReleased(GrabbedActor);
		ICursorInteractionInterface::Execute_ConstraintPhysics(GrabbedActor);
		GrabbedActor = nullptr;
	}
}

bool UWorldInteractorComponent::IsHitValidComponent(const UPrimitiveComponent* HitComponent)
{
	return HitComponent && HitComponent->GetAttachParent() && HitComponent->GetAttachParent()->GetClass()->ImplementsInterface(UCursorInteractionInterface::StaticClass());
}

void UWorldInteractorComponent::SetCursorVisibility(bool bVisibility)
{
	CursorDecal->SetVisibility(bVisibility);
}

