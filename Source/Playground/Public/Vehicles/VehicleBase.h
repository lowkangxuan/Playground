// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Components/ItemComponent.h"
#include "VehicleBase.generated.h"

class UInputMappingContext;
class UInputAction;
class UInteractableComponent;

UCLASS()
class PLAYGROUND_API AVehicleBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PC;

public:
	// Sets default values for this pawn's properties
	AVehicleBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInteractableComponent> InteractableComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DismountPlayer();
};
