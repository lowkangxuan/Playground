// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractIndicator.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UInteractIndicator : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractIndicator();

	FTimerHandle EffectTimer;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

private:
	UPROPERTY()
	TObjectPtr<UStaticMesh> CacheMesh;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> CacheMat;
	
	bool bIsActivated;
	FVector IndicatorScale;
	float Speed = 0.2f;
	float Alpha = 0;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActivateIndicator(bool bActivate);
};
