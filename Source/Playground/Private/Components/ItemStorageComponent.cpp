// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemStorageComponent.h"
#include "Items/ItemObject.h"
#include "CommonBlueprintHelpers.h"


// Sets default values for this component's properties
UItemStorageComponent::UItemStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	MaskArray.Init(false, GetTotalSize());
	TestMaskArray.Init(FRowStruct(StorageSize.X), StorageSize.Y);
}


// Called every frame
void UItemStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UItemObject* UItemStorageComponent::GenerateItemObject(UItemDataAsset* ItemData)
{
	if (ItemData == nullptr) return nullptr;

	UItemObject* NewItemObject = NewObject<UItemObject>(this, UItemObject::StaticClass());
	NewItemObject->ItemData = ItemData;

	return NewItemObject;
}

bool UItemStorageComponent::AttemptAddItem(UItemObject* Item)
{
	if (IsStorageFull()) return false;
	
	FVector2D ItemSize = Item->GetGridSize();
	TArray<int32> MaskIndexes;
	int32 Index = 0;
	bool bCanFit = false;

	for (Index; Index < MaskArray.Num(); ++Index)
	{
		bCanFit = CanItemFitAtIndex(Index, ItemSize, MaskIndexes);
		if (bCanFit) break;
	}

	if (!bCanFit) return false; // Item cannot be added
	
	StorageMap.Add(Item, UCommonBlueprintHelpers::IndexToGrid(Index, StorageSize));
	for (int32 i : MaskIndexes)
	{
		MaskArray[i] = true;
	}

	OnItemAddedDelegate.Broadcast(Item, UCommonBlueprintHelpers::IndexToGrid(Index, StorageSize), Index);
	return true;
}

bool UItemStorageComponent::AddItem(UItemObject* Item)
{
	//OnItemAddedDelegate.Broadcast(Item);
	return true;
}

bool UItemStorageComponent::RemoveItem(UItemObject* Item)
{
	FVector2D ItemSize = Item->GetGridSize();
	FVector2D GridLocation = StorageMap[Item];
	int32 Index = UCommonBlueprintHelpers::GridToIndex(GridLocation, StorageSize.Y);
	StorageMap.Remove(Item);

	for (int32 y = 0; y < ItemSize.Y; ++y)
	{
		for (int32 x = 0; x < ItemSize.X; ++x)
		{
			MaskArray[(Index + x) + (StorageSize.Y * y)] = false;
		}
	}

	OnItemRemovedDelegate.Broadcast(Item, GridLocation, Index);
	return true;
}

bool UItemStorageComponent::IsStorageFull()
{
	if (MaskArray.Contains(false)) return false; // At least one slot is still available
	
	return true;
}

bool UItemStorageComponent::CanItemFitAtIndex(int32 Index, FVector2D ItemSize, TArray<int32>& MaskIndexes)
{
	const FVector2D IndexGrid = UCommonBlueprintHelpers::IndexToGrid(Index, StorageSize);
	const FVector2D SizeToCheck = IndexGrid + ItemSize;

	if (SizeToCheck.X > StorageSize.X || SizeToCheck.Y > StorageSize.Y) return false;
	if (MaskArray[Index]) return false;

	for (int y = 0; y < ItemSize.Y; ++y)
	{
		for (int x = 0; x < ItemSize.X; ++x)
		{
			const uint16 a = (Index + x) + (StorageSize.Y * y);
			
			if (MaskArray[a]) return false;
			MaskIndexes.Add(a);
		}
	}

	return true;
}

int32 UItemStorageComponent::GetTotalSize()
{
	return StorageSize.X * StorageSize.Y;
}

int32 UItemStorageComponent::GetNumOfItems()
{
	return StorageMap.Num();
}

TArray<UItemObject*> UItemStorageComponent::GetAllItems()
{
	TArray<UItemObject*> TempItems;
	StorageMap.GetKeys(TempItems);

	return TempItems;
}

