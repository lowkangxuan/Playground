// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TooltipComponent.generated.h"

class UItemDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UTooltipComponent : public UActorComponent
{
	GENERATED_BODY()

private:

public:
	// Sets default values for this component's properties
	UTooltipComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void DisplayTooltip(UItemDataAsset* Info);

	UFUNCTION()
	void RemoveTooltip();
};
