// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Components/PickableComponent.h"
#include "Components/ItemComponent.h"
#include "Delegates/OnPickedUpDelegate.h"
#include "PhysicalItem.generated.h"

class UItemDataAsset;
class UInteractIndicator;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpSignature);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropSignature);

UCLASS()
class PLAYGROUND_API APhysicalItem : public AActor, public IInteractionInterface
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

	//UPROPERTY(BlueprintAssignable)
	//FOnPickUpSignature OnPickUpDelegate;
	//
	//UPROPERTY(BlueprintAssignable)
	//FOnDropSignature OnDropDelegate;

	UPROPERTY(BlueprintReadWrite)
	bool bIsPickedUp = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	virtual void Tick(float DeltaTime) override;
	void SetHighlight(bool bHighlight);

	// IItemInteractionInterface functions
	virtual void ConstraintPhysics_Implementation() override;
	virtual void OnMouseClicked_Implementation() override;
	virtual void OnCursorEnter_Implementation() override;
	virtual void OnCursorExit_Implementation() override;
	virtual void OnReleased_Implementation() override;
};
