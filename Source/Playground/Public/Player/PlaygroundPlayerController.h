// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlaygroundPlayerController.generated.h"

struct FInputActionInstance;
class UInputMappingContext;
class AHudManager;
class UItemObject;
class UWorldInteractorComponent;
class UPhysicsHandleComponent;

UCLASS()
class PLAYGROUND_API APlaygroundPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, DisplayName = "UI Mapping Context")
	TObjectPtr<UInputMappingContext> UIMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> EditorMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UWorldInteractorComponent> WorldInteractorComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	TObjectPtr<UPhysicsHandleComponent> PhysicsHandleComponent;
	
public:
	APlaygroundPlayerController();
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void InteractWithWorld();

	UFUNCTION()
	void InteractWithItem(const FInputActionInstance& Instance);

	UFUNCTION()
	void InteractCancelled();

	UFUNCTION()
	void RotateHandle(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void DropItem(UItemObject* ItemToDrop);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DisplayName="Get HUD Manager"))
	AHudManager* GetHudManager();
};
