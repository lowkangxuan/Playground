// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShieldInterface.h"
#include "GameFramework/Actor.h"
#include "ShieldBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class PLAYGROUND_API AShieldBase : public AActor, public IShieldInterface
{
	GENERATED_BODY()

public:
	AShieldBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShieldHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	float ActivationTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShieldDowntime = 5.0f;
	
	UPROPERTY(EditAnywhere)
	bool bShowShieldOnStart = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsShieldDestroyed = false;

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	float CachedShieldHealth;

	UPROPERTY(Transient, BlueprintReadOnly)
	float CachedShieldDowntime;

private:
	FTimerHandle ShieldDowntimeTimerHandle;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsShieldActivated = false;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TakeDamge_Implementation(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ActivateShield();

	UFUNCTION(BlueprintCallable)
	void DeactivateShield();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyShield();

private:
	UFUNCTION()
	void ShieldDowntimeCounter();
};
