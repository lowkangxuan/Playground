// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/SignalDelegate.h"
#include "InteractableComponent.generated.h"

class UItemDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCursorEnterInfo, class UItemDataAsset*, ItemInfo);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UItemDataAsset> InteractionData;

public:
	// Sets default values for this component's properties
	UInteractableComponent();
	
	UPROPERTY(BlueprintAssignable)
	FSignal OnCursorEnter;

	UPROPERTY(BlueprintAssignable)
	FOnCursorEnterInfo OnCursorEnterInfo;
	
	UPROPERTY(BlueprintAssignable)
	FSignal OnCursorExit;
	
	UPROPERTY(BlueprintAssignable)
	FSignal OnMouseClick;

	UPROPERTY(BlueprintAssignable)
	FSignal OnInteractSuccess;

	UPROPERTY(BlueprintAssignable)
	FSignal OnInteractCancelled;

	UPROPERTY()
	bool bIsHovered = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanInteract = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHasDelay = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 InteractionDelay = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void ProcessCursorEnter();
	virtual void ProcessCursorExit();
	virtual void ProcessMouseClick();
	virtual void ProcessInput();
	void SetInteractionData(UItemDataAsset* Data);
};
