// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

class UItemFragment;
class UNiagaraSystem;
class UItem;

UCLASS(BlueprintType)
class PLAYGROUND_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText DisplayName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FSlateBrush Icon;
	
	UPROPERTY(EditAnywhere, Instanced, meta=(ShowInnerProperties))
	TArray<TObjectPtr<UItemFragment>> Fragments;
	
	// The item class for the player to own
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UItem> OwnerItemClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(Delta = 1, Multiple = 1, ClampMin = 1))
	FVector2D GridSize = FVector2D(1, 1);

public:
	template<class T>
	T* GetFragmentByClass() const
	{
		return FindFragmentByClass<T>();	
	};

	/** Searches Fragments array and returns first encountered fragment of the specified class, native version of GetFragmentByClass */
	UItemFragment* FindFragmentByClass(const TSubclassOf<UItemFragment> FragmentClass) const;

	/** Templated version of FindFragmentByClass that handles casting for you.
	 *  Code hijacked from Actor.h
	 */
	template<class T>
	T* FindFragmentByClass() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, const UItemFragment>::Value, "'T' template parameter to FindFragmentByClass must be derived from UItemFragment");

		return (T*)FindFragmentByClass(T::StaticClass());
	}
};
