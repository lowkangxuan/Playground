// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class USphereComponent;
class UItemDataAsset;
class UNiagaraComponent;

UCLASS()
class PLAYGROUND_API AItemSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemSpawner();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> ItemCooldownMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> BaseNiagaraSystem;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> CooldownNiagaraSystem;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> CooldownMaterial;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UMaterialInstanceDynamic> CooldownMaterialInstance;

	UPROPERTY()
	float Cooldown;

	UPROPERTY()
	bool bIsItemAvailable = true;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UItemDataAsset> ItemData;

private:
	UPROPERTY()
	FTimerHandle ItemCooldownHandle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
	UFUNCTION()
	void AttemptPickup(const AActor* PlayerActor);
	
	UFUNCTION(BlueprintNativeEvent)
	void PlayPickupEffect();

	UFUNCTION(BlueprintNativeEvent)
	void PlayCooldownEndEffect();

	// Checks if player is still overlapping the spawner
	UFUNCTION()
	void CheckExistingOverlap();

	UFUNCTION()
	void SetItemAvailability(bool Available);

	UFUNCTION()
	void OnCooldownEnded();

private:
	
};
