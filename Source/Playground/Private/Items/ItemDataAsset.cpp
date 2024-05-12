// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemDataAsset.h"
#include "UObject/UObjectBaseUtility.h"
#include "Items/Fragments/ItemFragment.h"


UItemFragment* UItemDataAsset::FindFragmentByClass(const TSubclassOf<UItemFragment> FragmentClass) const
{
	if (FragmentClass != nullptr)
	{
		for (UItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}
	
	return nullptr;
}
