﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Items/ItemDataAsset.h"
#include "TooltipSubsystem.generated.h"

class ATooltipActor;

UCLASS()
class PLAYGROUND_API UTooltipSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<ATooltipActor> TooltipActor;

	UPROPERTY()
	TSubclassOf<AActor> TooltipClass;
	
public:
	UTooltipSubsystem();
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void ShowTooltip(const UItemDataAsset* Data, AActor* ItemActor, const FVector& SpawnOffset, float InteractionDelay);
	void HideTooltip();
	void SpawnTooltipActor();
};
