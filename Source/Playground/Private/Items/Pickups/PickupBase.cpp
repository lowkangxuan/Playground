// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Pickups/PickupBase.h"
#include "Components/ItemStorageComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
APickupBase::APickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");

	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetNotifyRigidBodyCollision(true); // Allows for hit events
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECC_WorldStatic);
	CollisionComponent->SetCollisionProfileName("BlockAll");
	MeshComponent->SetCollisionProfileName("NoCollision");
	MeshComponent->SetGenerateOverlapEvents(false);

	RootComponent = CollisionComponent;
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddUniqueDynamic(this, &APickupBase::OnCollision);
	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APickupBase::OnOverlap);
}

void APickupBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	CollisionComponent->OnComponentHit.RemoveAll(this); // Removes all subscribed delegates
	CollisionComponent->OnComponentBeginOverlap.RemoveAll(this); // Removes all subscribed delegates
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupBase::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Collided!"));
}

void APickupBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped!"));
	UItemStorageComponent* StorageComponent = OtherActor->GetComponentByClass<UItemStorageComponent>();
	if (StorageComponent != nullptr)
	{
		AttemptPickup(StorageComponent);
	}
}

void APickupBase::AttemptPickup(UItemStorageComponent* StorageComponent)
{
}

void APickupBase::PlayPickupEffect_Implementation()
{
}

void APickupBase::CheckExistingOverlap()
{
	GetOverlappingActors(OverlappingActors, APawn::StaticClass());
	if (OverlappingActors.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Player is overlapping!"));
		AttemptPickup(OverlappingActors[0]->GetComponentByClass<UItemStorageComponent>());
	}
}

