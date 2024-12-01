// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/SignalDelegate.h"
#include "InteractableComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableComponent();

	UPROPERTY(BlueprintAssignable)
	FSignal OnCursorEnter;
	
	UPROPERTY(BlueprintAssignable)
	FSignal OnCursorExit;
	
	UPROPERTY(BlueprintAssignable)
	FSignal OnMouseClick;

	UPROPERTY(BlueprintAssignable)
	FSignal OnInteractSuccess;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
