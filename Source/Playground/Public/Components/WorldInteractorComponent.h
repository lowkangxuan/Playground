// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldInteractorComponent.generated.h"

class ACursorDecal;
class UInteractableComponent;
class UPhysicsHandleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UWorldInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWorldInteractorComponent();

	UPROPERTY()
    TObjectPtr<AActor> CursorActor;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACursorDecal> CursorClass;

	UPROPERTY(EditDefaultsOnly)
	FVector HandleOffset = FVector(0, 0, 100);

private:
	UPROPERTY()
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandleComponent;
	
	UPROPERTY()
	TObjectPtr<UDecalComponent> CursorDecal;

	UPROPERTY()
	TObjectPtr<UInteractableComponent> HoveredInteractable;

	UPROPERTY(Transient)
	TObjectPtr<AActor> HoveredActor;

	UPROPERTY()
	TObjectPtr<AActor> GrabbedActor;

	bool bIsGrabbingItem;
	FVector RayEndLocation;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MouseToWorld();
	void AttemptItemGrabbing();
	void TriggerInputInteraction(float ElapsedTime);
	void InputInteractionCancelled();
	void RotateHeldItem(float InputDelta);

private:
	static bool IsHitValidActor(const AActor* HitActor);
	void SetCursorVisibility(bool bVisibility = true);
};
