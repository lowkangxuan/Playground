#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlaygroundSystemLibrary.generated.h"

UCLASS()
class HELPERS_API UPlaygroundSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static TArray<FAssetData> GetPhysicalItemAssets();

	/*
	 * Code yoinked from https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/AssetRegistry/Private/AssetRegistryHelpers.cpp
	 * because for some reason it was just meant to be a Blueprint-only usable function
	 */
#if WITH_EDITOR
	static bool IsAssetDataBlueprintOfClassSet(const FAssetData& AssetData, const TSet<FTopLevelAssetPath>& ClassNameSet);
	static void GetBlueprintAssets(const FARFilter& InFilter, TArray<FAssetData>& OutAssetData);
#endif
};
