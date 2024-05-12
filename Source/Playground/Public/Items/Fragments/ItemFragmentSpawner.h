// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "ItemFragmentSpawner.generated.h"

/**
 * 
 */
UCLASS()
class PLAYGROUND_API UItemFragmentSpawner : public UItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	float Cooldown = 10.0f;
	
	UPROPERTY(EditAnywhere, Category="Attributes")
	int32 Quantity = 1;
	
	UPROPERTY(EditAnywhere, Category="Appearance")
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, Category="Appearance")
	FVector MeshOffset;
};
