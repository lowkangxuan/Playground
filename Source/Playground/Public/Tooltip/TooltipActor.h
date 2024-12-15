// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TooltipActor.generated.h"

class UWidgetComponent;
class UTooltipCard;

UCLASS()
class PLAYGROUND_API ATooltipActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATooltipActor();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tooltip")
	TObjectPtr<UTooltipCard> TooltipWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
