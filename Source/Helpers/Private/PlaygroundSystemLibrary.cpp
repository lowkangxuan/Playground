// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundSystemLibrary.h"

#include "AssetRegistry/AssetRegistryHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Items/PhysicalItem.h"

TArray<FAssetData> UPlaygroundSystemLibrary::GetPhysicalItemAssets()
{
	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	FARFilter Filter;
	Filter.ClassPaths.Add(FTopLevelAssetPath(APhysicalItem::StaticClass()->GetClassPathName()));
	UE_LOG(LogTemp, Log, TEXT("%s"), *(APhysicalItem::StaticClass()->GetClassPathName().ToString()));
	Filter.bRecursiveClasses = true;
	Filter.bRecursivePaths = true;
	TArray<FAssetData> Assets;
	GetBlueprintAssets(Filter, Assets);
	Assets.Sort();
	return Assets;
}

#if WITH_EDITOR
bool UPlaygroundSystemLibrary::IsAssetDataBlueprintOfClassSet(const FAssetData& AssetData, const TSet<FTopLevelAssetPath>& ClassNameSet)
{
	const FString ParentClassFromData = AssetData.GetTagValueRef<FString>(FBlueprintTags::ParentClassPath);
	if (!ParentClassFromData.IsEmpty())
	{
		const FTopLevelAssetPath ClassObjectPath(FPackageName::ExportTextPathToObjectPath(ParentClassFromData));
		const FName ClassName = ClassObjectPath.GetAssetName();

		TArray<FTopLevelAssetPath> ValidNames;
		ValidNames.Add(ClassObjectPath);
		// Check for redirected name
		FTopLevelAssetPath RedirectedName = FTopLevelAssetPath(FLinkerLoad::FindNewPathNameForClass(ClassObjectPath.ToString(), false));
		if (!RedirectedName.IsNull())
		{
			ValidNames.Add(RedirectedName);
		}
		for (const FTopLevelAssetPath& ValidName : ValidNames)
		{
			if (ClassNameSet.Contains(ValidName))
			{
				// Our parent class is in the class name set
				return true;
			}
		}
	}
	return false;
}

void UPlaygroundSystemLibrary::GetBlueprintAssets(const FARFilter& InFilter, TArray<FAssetData>& OutAssetData)
{
	IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();

	FARFilter Filter(InFilter);
	PRAGMA_DISABLE_DEPRECATION_WARNINGS;
	UE_CLOG(!InFilter.ClassNames.IsEmpty(), LogCore, Error,
		TEXT("ARFilter.ClassNames is not supported by UAssetRegistryHelpers::GetBlueprintAssets and will be ignored."));
	Filter.ClassNames.Empty();
	PRAGMA_ENABLE_DEPRECATION_WARNINGS;

	// Expand list of classes to include derived classes
	TArray<FTopLevelAssetPath> BlueprintParentClassPathRoots = MoveTemp(Filter.ClassPaths);
	TSet<FTopLevelAssetPath> BlueprintParentClassPaths;
	if (Filter.bRecursiveClasses)
	{
		AssetRegistry.GetDerivedClassNames(BlueprintParentClassPathRoots, TSet<FTopLevelAssetPath>(), BlueprintParentClassPaths);
	}
	else
	{
		BlueprintParentClassPaths.Append(BlueprintParentClassPathRoots);
	}

	// Search for all blueprints and then check BlueprintParentClassPaths in the results
	Filter.ClassPaths.Reset(1);
	Filter.ClassPaths.Add(FTopLevelAssetPath(FName(TEXT("/Script/Engine")), FName(TEXT("BlueprintCore"))));
	Filter.bRecursiveClasses = true;

	auto FilterLambda = [&OutAssetData, &BlueprintParentClassPaths](const FAssetData& AssetData)
	{
		// Verify blueprint class
		if (BlueprintParentClassPaths.IsEmpty() || IsAssetDataBlueprintOfClassSet(AssetData, BlueprintParentClassPaths))
		{
			OutAssetData.Add(AssetData);
		}
		return true;
	};
	AssetRegistry.EnumerateAssets(Filter, FilterLambda); 
}
#endif