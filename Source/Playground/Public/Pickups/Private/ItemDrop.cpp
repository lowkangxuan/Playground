// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/Public/ItemDrop.h"
#include "Components/SphereComponent.h"
#include "Components/ItemStorageComponent.h"

// Sets default values
AItemDrop::AItemDrop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemDrop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemDrop::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnCollision(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	CollisionComponent->SetSimulatePhysics(false);
	CollisionComponent->SetCollisionProfileName("OverlapAll");
}

void AItemDrop::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UItemStorageComponent* StorageComponent = OtherActor->GetComponentByClass<UItemStorageComponent>();
	if (StorageComponent != nullptr)
	{
		if (StorageComponent->AttemptAddItem(ItemObject)) Destroy();
	}
}

