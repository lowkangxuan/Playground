// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarPowerComponent.generated.h"

class ASky;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSunlightReceivedSignature, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSunlightBlockedSignature);

// Gather power from direct sunlight only
// Power can be stored in a PowerComponent
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API USolarPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USolarPowerComponent();

	bool bIsReceivingSunlight = true;
	bool bWasReceivingSunlightLastFrame = true;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USceneComponent> CastComponent;

	UPROPERTY(BlueprintAssignable)
	FOnSunlightReceivedSignature OnSunlightReceivedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnSunlightBlockedSignature OnSunlightBlockedDelegate;

private:
	UPROPERTY()
	TObjectPtr<ASky> SkyActor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
