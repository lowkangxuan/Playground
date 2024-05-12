// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonBlueprintHelpers.generated.h"

class UInputAction;
class APlaygroundGameMode;
class UPlaygroundGameInstance;

UCLASS()
class HELPERS_API UCommonBlueprintHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static bool IsWithEditor();

	UFUNCTION(BlueprintPure)
	static FVector2D IndexToGrid(int32 Index, FVector2D GridSize);

	UFUNCTION(BlueprintPure)
	static int32 GridToIndex(FVector2D Grid, int32 SizeY);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static bool CheckIfKeyInputsAreSimilar(const UObject* WorldContext, FKey PressedKey, UInputAction* InputAction);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static APlaygroundGameMode* GetPlaygroundGameMode(const UObject* WorldContext, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static UPlaygroundGameInstance* GetPlaygroundGameInstance(const UObject* WorldContext, bool& bSuccess);
};
