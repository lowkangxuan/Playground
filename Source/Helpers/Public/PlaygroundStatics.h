// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlaygroundStatics.generated.h"

class UInputAction;
class APlaygroundGameMode;
class UPlaygroundGameInstance;
class APlaygroundPlayerController;
class APlaygroundCharacter;
class AHudManager;

UCLASS()
class HELPERS_API UPlaygroundStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static bool IsWithEditor();

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static bool CheckIfKeyInputsAreSimilar(const UObject* WorldContext, FKey PressedKey, UInputAction* InputAction);

	UFUNCTION(BlueprintPure)
	static FVector2D ClampIndividualAxes2D(FVector2D A, float MinX, float MaxX, float MinY, float MaxY);
	
	UFUNCTION(BlueprintPure)
	static FVector2D IndexToGrid(int32 Index, FVector2D GridSize);

	UFUNCTION(BlueprintPure)
	static int32 GridToIndex(FVector2D Grid, int32 SizeX);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static APlaygroundCharacter* GetPlaygroundCharacter(const UObject* WorldContext);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static APlaygroundPlayerController* GetPlaygroundPlayerController(const UObject* WorldContext);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static APlaygroundGameMode* GetPlaygroundGameMode(const UObject* WorldContext);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext"))
	static UPlaygroundGameInstance* GetPlaygroundGameInstance(const UObject* WorldContext);
	
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContext", DisplayName="Get HUD Manager"))
	static AHudManager* GetHudManager(const UObject* WorldContext);
};
