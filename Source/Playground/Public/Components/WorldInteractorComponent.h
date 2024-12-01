// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldInteractorComponent.generated.h"

class UPhysicsHandleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UWorldInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWorldInteractorComponent();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInterface> DecalMat;

private:
	UPROPERTY()
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandleComponent;
	
	UPROPERTY()
	TObjectPtr<UDecalComponent> CursorDecal;

	bool bIsGrabbingItem;
	FVector RayEndLocation;

	UPROPERTY(Transient)
	TObjectPtr<AActor> HoveredActor;
	
	UPROPERTY(Transient)
	TObjectPtr<UPrimitiveComponent> HoveredComp;

	UPROPERTY()
	TObjectPtr<AActor> GrabbedActor;

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> GrabbedComp;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void MouseToWorld();
	void AttemptInteraction();

private:
	bool InteractWithComponent();
	bool InteractWithActor();
	static bool IsHitValidComponent(const UPrimitiveComponent* HitComponent);
	static bool IsHitValidActor(const AActor* HitActor);
	void SetCursorVisibility(bool bVisibility = true);
};
