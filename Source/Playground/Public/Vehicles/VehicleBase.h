// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Interfaces/InteractionInterface.h"
#include "Components/PickableComponent.h"
#include "VehicleBase.generated.h"

UCLASS()
class PLAYGROUND_API AVehicleBase : public AWheeledVehiclePawn, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicleBase();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPickableComponent> PickableComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void ConstraintPhysics_Implementation() override;
	virtual void OnMouseClicked_Implementation() override;
	virtual void OnCursorEnter_Implementation() override;
	virtual void OnCursorExit_Implementation() override;
	virtual void OnReleased_Implementation() override;
};
