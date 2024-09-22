// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemStorageComponent.h"
#include "Items/ItemObject.h"
#include "PlaygroundStatics.h"


// Sets default values for this component's properties
UItemStorageComponent::UItemStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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

	for (int32 i = 0; i < MaskArray.Num(); ++i)
	{
		if (CanItemFitAtIndex(i, ItemSize))
		{
			AddItem(Item, i);
			return true;
		}
	}
	
	return false;
}

void UItemStorageComponent::AddItem(UItemObject* Item, int32 Index)
{
	FVector2D ItemSize = Item->GetGridSize();
	FVector2D IndexGrid = UPlaygroundStatics::IndexToGrid(Index, StorageSize);
	int32 XBound = 0 - (int32(ItemSize.X - 1) / 2);
	int32 YBound = 0 - (int32(ItemSize.Y - 1) / 2);
	
	StorageMap.Add(Item, IndexGrid); // Add the item to the map
	
	// Modifying the mask array to indicate slot being taken
	for (int32 Y = YBound; Y < ItemSize.Y + YBound; ++Y)
	{
		for (int32 X = XBound; X < ItemSize.X + XBound; ++X)
		{
			const uint16 a = UPlaygroundStatics::GridToIndex(IndexGrid + FVector2D(X, Y), StorageSize.X);
			MaskArray[a] = true;
		}
	}
	
	OnItemAddedDelegate.Broadcast(Item, UPlaygroundStatics::IndexToGrid(Index, StorageSize), Index);
}

bool UItemStorageComponent::RemoveItem(UItemObject* Item)
{
	FVector2D ItemSize = Item->GetGridSize();
	FVector2D GridLocation = StorageMap[Item];
	int32 Index = UPlaygroundStatics::GridToIndex(GridLocation, StorageSize.X);
	int32 XBound = 0 - (int32(ItemSize.X - 1) / 2);
	int32 YBound = 0 - (int32(ItemSize.Y - 1) / 2);
	
	StorageMap.Remove(Item);

	for (int32 Y = YBound; Y < ItemSize.Y + YBound; ++Y)
	{
		for (int32 X = XBound; X < ItemSize.X + XBound; ++X)
		{
			MaskArray[UPlaygroundStatics::GridToIndex(UPlaygroundStatics::IndexToGrid(Index, StorageSize) + FVector2D(X, Y), StorageSize.X)] = false;
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

bool UItemStorageComponent::CanItemFitAtIndex(int32 Index, FVector2D ItemSize)
{
	const int32 XBound = 0 - (int32(ItemSize.X - 1) / 2);
	const int32 YBound = 0 - (int32(ItemSize.Y - 1) / 2);
	const FVector2D IndexGrid = UPlaygroundStatics::IndexToGrid(Index, StorageSize);
	const FVector2D SizeToCheck = IndexGrid + (ItemSize / 2);

	if (SizeToCheck.X > StorageSize.X || SizeToCheck.Y > StorageSize.Y) return false;
	if (MaskArray[Index]) return false;
	
	for (int32 Y = YBound; Y < ItemSize.Y + YBound; ++Y)
	{
		for (int32 X = XBound; X < ItemSize.X + XBound; ++X)
		{
			FVector2D GridToCheck = IndexGrid + FVector2D(X, Y);
			if (GridToCheck.X < 0 || GridToCheck.X > StorageSize.X - 1 || GridToCheck.Y < 0 || GridToCheck.Y > StorageSize.Y - 1) return false;
			if (MaskArray[UPlaygroundStatics::GridToIndex(GridToCheck, StorageSize.X)]) return false;
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

