// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "ButtonComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedSignature);

UENUM()
enum EButtonShape
{
	Cube,
	Cylinder
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UButtonComponent : public UPrimitiveComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UButtonComponent();

	UPROPERTY(BlueprintAssignable)
	FOnButtonClickedSignature OnButtonClicked;
	
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EButtonShape> ButtonShape = EButtonShape::Cube;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> IconMesh;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPreserveRatio))
	FVector IconScale = FVector(1);
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> ButtonCollision;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> ShellComponent;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> IconComponent;
	
	UPROPERTY()
	TObjectPtr<UStaticMesh> CubeMesh;
	
	UPROPERTY()
	TObjectPtr<UStaticMesh> CylinderMesh;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> ShellMaterial;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnMouseClicked_Implementation() override;
	virtual void OnCursorEnter_Implementation() override;
	virtual void OnCursorExit_Implementation() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Enable(bool bEnabled);
};
