// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PickableComponent.h"
#include "Components/ItemComponent.h"
#include "Delegates/SignalDelegate.h"
#include "PhysicalItem.generated.h"

class UItemDataAsset;
class UInteractIndicator;

UCLASS()
class PLAYGROUND_API APhysicalItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APhysicalItem();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> IndicatorMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInteractIndicator> IndicatorUX;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPickableComponent> PickableComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UItemComponent> ItemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UItemDataAsset> ItemData;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnCursorEnter();
	
	UFUNCTION()
	void OnCursorExit();
	
	UFUNCTION()
	void OnItemPickUp();

	UFUNCTION()
	void OnItemDrop();

	UFUNCTION()
	void EnableHighlight();

	UFUNCTION()
	void DisableHighlight();
};
