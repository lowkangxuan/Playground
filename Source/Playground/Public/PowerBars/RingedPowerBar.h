// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerBarBase.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "RingedPowerBar.generated.h"

UCLASS()
class PLAYGROUND_API ARingedPowerBar : public APowerBarBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARingedPowerBar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> MeshGroup;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> SpacerMeshes;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> RingMeshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> SourceMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> InactiveMat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> OffMat;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 1))
	int32 RingCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 1))
	int32 Row = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin = 0))
	float Scale = 1;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Active(float Delta);
	virtual void Inactive();

protected:
	void GenerateBars();
};
