// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/CursorInteractionInterface.h"
#include "PhysicalItem.generated.h"

class UItemDataAsset;
class UInteractIndicator;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropSignature);

UCLASS()
class PLAYGROUND_API APhysicalItem : public AActor, public ICursorInteractionInterface
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UItemDataAsset> ItemData;

	UPROPERTY(BlueprintAssignable)
	FOnPickUpSignature OnPickUpDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDropSignature OnDropDelegate;

	UPROPERTY(BlueprintReadWrite)
	bool bIsPickedUp = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsOverlapping = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	virtual void Tick(float DeltaTime) override;
	void SetHighlight(bool bHighlight);

	// IItemInteractionInterface functions
	virtual void ConstraintPhysics_Implementation() override;
	virtual void OnMouseClicked_Implementation() override;
	virtual void OnCursorEnter_Implementation() override;
	virtual void OnCursorExit_Implementation() override;
};
