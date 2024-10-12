// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlaygroundPlayerController.generated.h"

class APlaygroundCharacter;
class UInputMappingContext;
class UInputAction;
class AHudManager;
class UItemObject;

UCLASS()
class PLAYGROUND_API APlaygroundPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> PlayerMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, DisplayName = "UI Mapping Context", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> UIMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> EditorMappingContext;

public:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UFUNCTION(BlueprintCallable)
	void DropItem(UItemObject* ItemToDrop);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DisplayName="Get HUD Manager"))
	AHudManager* GetHudManager();
};
