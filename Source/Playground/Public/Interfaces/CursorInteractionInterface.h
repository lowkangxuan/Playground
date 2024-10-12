// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CursorInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UCursorInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class PLAYGROUND_API ICursorInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnMouseClicked();

	// Similar to OnHoverEnter
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCursorEnter();

	// Similar to OnHoverExit
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnCursorExit();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnReleased();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ConstraintPhysics();
};
