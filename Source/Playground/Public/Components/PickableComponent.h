// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "PickableComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UPickableComponent : public UInteractableComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPickableComponent();

	UPROPERTY(BlueprintAssignable)
	FSignal OnPickUp;

	UPROPERTY(BlueprintAssignable)
	FSignal OnDrop;

	UPROPERTY(BlueprintReadWrite)
	bool bIsPickedUp = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPrimitiveComponent> OwnerRoot;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void ProcessMouseClick() override;

	UFUNCTION(BlueprintCallable)
	void ConstraintPhysics();
};
