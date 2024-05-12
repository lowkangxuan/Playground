// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemStorageComponent.generated.h"

class UItem;
class UItemObject;
class UItemDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemAddedSignature, UItemObject*, NewItem, FVector2D, AddedGrid, int32, AddedIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemRemovedSignature, UItemObject*, RemovedItem, FVector2D, RemovedGrid, int32, RemovedIndex);

USTRUCT()
struct FRowStruct
{
	GENERATED_BODY()
	FRowStruct()
		: Row(TArray<bool>({}))
	{}

	FRowStruct(int32 Columns)
	{
		Row.Init(false, Columns);
	}

	UPROPERTY(VisibleAnywhere)
	TArray<bool> Row;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UItemStorageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemStorageComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
	TMap<UItemObject*, FVector2D> StorageMap;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(ClampMin = 0, Multiple = 1))
	FVector2D StorageSize = FVector2D(5, 5);

	UPROPERTY(BlueprintAssignable)
	FOnItemAddedSignature OnItemAddedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnItemRemovedSignature OnItemRemovedDelegate;

private:
	UPROPERTY(Transient, VisibleAnywhere)
	TArray<bool> MaskArray;

	UPROPERTY(Transient, VisibleAnywhere)
	TArray<FRowStruct> TestMaskArray;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	UItemObject* GenerateItemObject(UItemDataAsset* ItemData);
	
	UFUNCTION(BlueprintCallable)
	bool AttemptAddItem(UItemObject* Item);

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItemObject* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItemObject* Item);

	UFUNCTION(BlueprintCallable)
	bool IsStorageFull();

	UFUNCTION(BlueprintCallable)
	bool CanItemFitAtIndex(int32 Index, FVector2D ItemSize, TArray<int32>& MaskIndexes);

	UFUNCTION(BlueprintGetter)
	int32 GetTotalSize();

	UFUNCTION(BlueprintGetter)
	int32 GetNumOfItems();

	UFUNCTION(BlueprintGetter)
	TArray<UItemObject*> GetAllItems();
};
