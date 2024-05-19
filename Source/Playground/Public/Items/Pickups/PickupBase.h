// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class USphereComponent;
class UItemStorageComponent;

UCLASS()
class PLAYGROUND_API APickupBase : public AActor
{
	GENERATED_BODY()

public:
	APickupBase();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

protected:
	UPROPERTY(VisibleAnywhere, Transient)
	TArray<TObjectPtr<AActor>> OverlappingActors;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

protected:
	virtual void AttemptPickup(UItemStorageComponent* StorageComponent);

	UFUNCTION(BlueprintNativeEvent)
	void PlayPickupEffect();

	virtual void CheckExistingOverlap();
};
