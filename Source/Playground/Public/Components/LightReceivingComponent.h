// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightReceivingComponent.generated.h"

class ASky;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSunlightReceivedSignature, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSunlightBlockedSignature);

UCLASS(Abstract)
class PLAYGROUND_API ULightReceivingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULightReceivingComponent();

	bool bIsReceivingSunlight = true;
	bool bWasReceivingSunlightLastFrame = true;

	UPROPERTY(EditDefaultsOnly)
	float MaxSunAngle = 75.0f;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USceneComponent> CastComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ASky> SkyActor;

	UPROPERTY(BlueprintAssignable)
	FOnSunlightReceivedSignature OnSunlightReceivedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnSunlightBlockedSignature OnSunlightBlockedDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
