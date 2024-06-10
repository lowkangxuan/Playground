// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ItemInteractionInterface.h"
#include "PhysicalItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickedUpSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDroppedSignature);

UCLASS()
class PLAYGROUND_API APhysicalItem : public AActor, public IItemInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APhysicalItem();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> IndicatorMesh;

	UPROPERTY(BlueprintAssignable)
	FOnPickedUpSignature OnPickedUpDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDroppedSignature OnDroppedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//virtual void SetPickedup_Implementation(bool PickedUp) override;
	//
	//// Zeroes out the linear and angular velocity of the item
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void ConstraintPhysics();
	
	virtual void SetPickedup_Implementation(bool bPickedup) override;
	virtual void ConstraintPhysics_Implementation() override;
	virtual void HighlightItem_Implementation(bool bHighlight) override;
};
