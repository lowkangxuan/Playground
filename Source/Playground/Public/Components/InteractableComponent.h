// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/SignalDelegate.h"
#include "InteractableComponent.generated.h"

class UItemDataAsset;
class UTooltipComponent;
class UTooltipSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCursorEnterInfo, class UItemDataAsset*, ItemInfo);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UItemDataAsset> ItemData;

	UPROPERTY()
	TObjectPtr<UTooltipComponent> TooltipComponent;

private:
	UPROPERTY()
	TObjectPtr<UTooltipSubsystem> TooltipSubsystem;

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

	UPROPERTY(BlueprintReadWrite)
	bool bCanInteract = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction, meta=(ClampMin=0))
	float InteractionDelay = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Tooltip)
	FVector TooltipOffset = FVector(0, 0, 100);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void ProcessCursorEnter();
	virtual void ProcessCursorExit();
	virtual void ProcessMouseClick();

	UFUNCTION(BlueprintCallable)
	virtual void ProcessInput(float ElapsedTime);
	void InputCancelled();
	void ResetInput();

	UFUNCTION(BlueprintSetter)
	void SetItemData(UItemDataAsset* Data);

	UFUNCTION(BlueprintCallable)
	void ToggleTooltipState(bool bShow);
};
