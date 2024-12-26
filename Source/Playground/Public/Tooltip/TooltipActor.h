// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TooltipActor.generated.h"

struct FTooltipInfo;
class UWidgetComponent;
class UTooltipWidget;

UCLASS()
class PLAYGROUND_API ATooltipActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATooltipActor();

	UPROPERTY()
	FVector Offset;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> HoveringActor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTooltipWidget> TooltipWidget;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetActorHiddenInGame(bool bNewHidden) override;
};
