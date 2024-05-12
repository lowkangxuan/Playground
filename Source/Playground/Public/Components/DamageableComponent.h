// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPostDamageTakenSignature, float, NewHealth, float, NewArmor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAYGROUND_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageableComponent();

	UPROPERTY(BlueprintAssignable)
	FOnPostDamageTakenSignature OnPostDamageTakenDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	float BaseHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
	float BaseArmor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintNativeEvent)
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCause);
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void CalculateDamageInput(float InDamage);
};
