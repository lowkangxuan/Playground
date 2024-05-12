// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyShooter.generated.h"

class AProjectileBase;

UCLASS(Blueprintable)
class PLAYGROUND_API ADummyShooter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADummyShooter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectileBase> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectileBase> NewProjectile;
	
	UPROPERTY(EditAnywhere, meta=(Tooltip="Interval between each shot"))
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MakeEditWidget))
	TArray<FVector>ProjectileSpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShootBurst = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShootBurst"))
	int32 BurstShots = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bShootBurst"))
	float BurstRate = 0.15f;

	UPROPERTY(VisibleAnywhere)
	int32 RemainingBurstShots = 0;

private:
	FTimerHandle ShootTimerHandle;
	FTimerHandle BurstShootingTimerHandle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();

	UFUNCTION()
	void BurstFire();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnProjectile();

	// Helper function for Blueprint to do whatever we want went a projectile is spawned
	// I.E. Play audio, spawn particles, activate a certain event, etc
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnProjectileSpawn();
};
