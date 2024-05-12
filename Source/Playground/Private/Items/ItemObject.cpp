// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemObject.h"

#include "Items/ItemDataAsset.h"

FVector2D UItemObject::GetGridSize()
{
	return ItemData->GridSize;
}

FSlateBrush UItemObject::GetIcon()
{
	return ItemData->Icon;
}
