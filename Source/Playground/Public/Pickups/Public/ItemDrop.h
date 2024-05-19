// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Pickups/PickupBase.h"
#include "ItemDrop.generated.h"

class UItemObject;

UCLASS()
class PLAYGROUND_API AItemDrop : public APickupBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemDrop();

	TObjectPtr<UItemObject> ItemObject;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
