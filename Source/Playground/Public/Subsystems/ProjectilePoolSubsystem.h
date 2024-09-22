// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ProjectilePoolSubsystem.generated.h"

class AProjectileBase;

UCLASS()
class PLAYGROUND_API UProjectilePoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AProjectileBase>> ProjectilePool;
	uint16 InitialPoolSize = 100;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	AProjectileBase* RetrieveFromPool();

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(AProjectileBase* ProjectileToReturn);

private:
	void CreateProjectile();
};
