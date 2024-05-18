// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Pickups/PickupBase.h"

#include "Components/SphereComponent.h"


// Sets default values
APickupBase::APickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APickupBase::OnCollision);
}

void APickupBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	CollisionComponent->OnComponentBeginOverlap.RemoveAll(this); // Removes all subscribed delegates
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupBase::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Collided!"));
	AttemptPickup(OtherActor);
}

void APickupBase::AttemptPickup(const AActor* PlayerActor)
{
}

void APickupBase::PlayPickupEffect_Implementation()
{
}

void APickupBase::CheckExistingOverlap()
{
	GetOverlappingActors(OverlappingActors, TSubclassOf<APawn>());
	if (OverlappingActors.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Player is overlapping!"));
		AttemptPickup(OverlappingActors[0]);
	}
}

