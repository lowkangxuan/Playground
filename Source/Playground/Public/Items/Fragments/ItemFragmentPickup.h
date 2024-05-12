// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "ItemFragmentPickup.generated.h"

class UNiagaraSystem;

UCLASS()
class PLAYGROUND_API UItemFragmentPickup : public UItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Effects")
	TObjectPtr<UNiagaraSystem> PickupVisualEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Effects")
	TObjectPtr<USoundBase> PickupSoundEffect;
};
