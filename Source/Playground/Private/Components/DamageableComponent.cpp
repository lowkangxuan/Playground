// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageableComponent.h"


// Sets default values for this component's properties
UDamageableComponent::UDamageableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();

	BaseHealth = Health;
	BaseArmor = Armor;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UDamageableComponent::TakeDamage);
}

void UDamageableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetOwner()->OnTakeAnyDamage.RemoveAll(this);
}

// Called every frame
void UDamageableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageableComponent::TakeDamage_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCause)
{
	CalculateDamageInput(Damage);
}

void UDamageableComponent::CalculateDamageInput(float InDamage)
{
	float UndealtDamage = InDamage;

	// Deal damage to Armor first
	Armor -= UndealtDamage;
	UndealtDamage = 0;
	if (Armor < 0) // Ensure that Armor does not fall below 0, and deal the remaining value to Health instead
	{
		UndealtDamage = FMath::Abs(Armor); // Getting the remaining value
		Armor = 0;
	}

	Health -= UndealtDamage;

	OnPostDamageTakenDelegate.Broadcast(Health, Armor);
}