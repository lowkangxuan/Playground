// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShieldInterface.generated.h"

UINTERFACE(BlueprintType)
class UShieldInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLAYGROUND_API IShieldInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void TakeDamge(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
};
