// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sky.generated.h"

UCLASS()
class PLAYGROUND_API ASky : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASky();

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> SkyBox;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UDirectionalLightComponent> Sun;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UDirectionalLightComponent> Moon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UMaterialInstanceDynamic> SkyMat;

	UPROPERTY(BlueprintReadOnly)
	float Time;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bPlayInEditor = true;
#endif
	
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UCurveLinearColor> HorizonCurve;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UCurveLinearColor> ZenithCurve;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UCurveFloat> CloudCurve;
	
private:
	UPROPERTY(EditInstanceOnly, Transient)
	bool bToggleSkyRefresh = false;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void UpdateSky();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	FVector GetSunForward();
	
	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetSunHeight() const;
};
