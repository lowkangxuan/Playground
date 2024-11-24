// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/InteractionInterface.h"
#include "PickableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoverEnterSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoverExitSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UPickableComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPickableComponent();

	UPROPERTY(BlueprintReadWrite)
	bool bIsPickedUp = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPrimitiveComponent> OwnerRoot;

	UPROPERTY(BlueprintAssignable)
	FOnPickUpSignature OnPickUpDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDropSignature OnDropDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnHoverEnterSignature OnHoverEnterDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHoverExitSignature OnHoverExitDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnPickUp();

	UFUNCTION(BlueprintNativeEvent)
	void OnRelease();

	UFUNCTION(BlueprintNativeEvent)
	void OnHoverEnter();

	UFUNCTION(BlueprintNativeEvent)
	void OnHoverExit();

	UFUNCTION(BlueprintCallable)
	void ConstraintPhysic();

	virtual void ConstraintPhysics_Implementation() override;
	virtual void OnMouseClicked_Implementation() override;
	virtual void OnCursorEnter_Implementation() override;
	virtual void OnCursorExit_Implementation() override;
	virtual void OnReleased_Implementation() override;
};
