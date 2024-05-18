// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items/Pickups/PickupBase.h"
#include "ItemSpawner.generated.h"

class USphereComponent;
class UItemDataAsset;
class UNiagaraComponent;

UCLASS()
class PLAYGROUND_API AItemSpawner : public APickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemSpawner();

	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<USphereComponent> CollisionComponent;

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

	virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void AttemptPickup(const AActor* PlayerActor) override;

	virtual void PlayPickupEffect_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
	void PlayCooldownEndEffect();

	// Checks if player is still overlapping the spawner
	virtual void CheckExistingOverlap() override;
	void SetItemAvailability(bool Available);
	void OnCooldownEnded();

private:
	
};
