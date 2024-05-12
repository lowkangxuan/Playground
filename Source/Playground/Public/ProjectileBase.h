// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS(Abstract)
class PLAYGROUND_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0, ClampMax=1, Delta=0.01))
	float CritPercentage = 0.0f;

	UPROPERTY(EditAnywhere)
	float CritMultipler = 2.0f;
	
	UPROPERTY(EditAnywhere)
	float LifeSpan = 2.0f;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	float CalculateOutgoingDamage();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireTowardsDir(const FVector Dir);

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
