// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicalItem.generated.h"

UCLASS()
class PLAYGROUND_API APhysicalItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APhysicalItem();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> RootMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
