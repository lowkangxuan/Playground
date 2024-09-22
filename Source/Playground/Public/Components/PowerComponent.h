// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerComponent.generated.h"

class APhysicalItem;
class ULightReceivingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFullChargeSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFullDischargeSignature);

// Stores power from incoming power source
// Discharges power from its remaining capacity
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UPowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPowerComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnFullChargeSignature OnFullCharge;

	UPROPERTY(BlueprintAssignable)
	FOnFullDischargeSignature OnFullDischarge;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bEnabled = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFullyCharged = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0))
	float MaxCapacity = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentPower = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0))
	float ChargeRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0))
	float DischargeRate = 0.0f;

private:
	TObjectPtr<ULightReceivingComponent> SolarPowerComponent;
	TObjectPtr<APhysicalItem> OwnerItem;
	 
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Charge(float Delta);

	UFUNCTION(BlueprintCallable)
	void Discharge(float Delta);

	UFUNCTION(BlueprintSetter)
	void SetEnabled();

	UFUNCTION(BlueprintSetter)
	void SetDisabled();
};
