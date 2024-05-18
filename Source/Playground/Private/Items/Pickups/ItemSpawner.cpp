// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Pickups/ItemSpawner.h"
#include "NiagaraComponent.h"
#include "Components/ItemStorageComponent.h"
#include "Components/SphereComponent.h"
#include "Items/ItemDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Items/ItemObject.h"
#include "Items/Fragments/ItemFragmentPickup.h"
#include "Items/Fragments/ItemFragmentSpawner.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
	BaseNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>("Base Niagara Component");
	CooldownNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>("Cooldown Niagara Component");
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Item Mesh");
	ItemCooldownMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cooldown Mesh");

	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemCooldownMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemCooldownMesh->SetVisibility(false);

	//SetRootComponent(CollisionComponent);
	BaseNiagaraSystem->SetupAttachment(RootComponent);
	CooldownNiagaraSystem->SetupAttachment(RootComponent);
	ItemMesh->SetupAttachment(RootComponent);
	ItemCooldownMesh->SetupAttachment(RootComponent);
}

void AItemSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CooldownMaterialInstance = UMaterialInstanceDynamic::Create(CooldownMaterial, this);
	ItemCooldownMesh->SetMaterial(0, CooldownMaterialInstance);

	ItemMesh->SetRelativeRotation(FRotator(0, -90, 0));
	ItemCooldownMesh->SetRelativeRotation(FRotator(0, -90, 0));

	if (ItemData != nullptr)
	{
		UItemFragmentSpawner* SpawnerFragment = ItemData->GetFragmentByClass<UItemFragmentSpawner>();
		if (SpawnerFragment != nullptr)
		{
			Cooldown = SpawnerFragment->Cooldown;
			
			ItemMesh->SetStaticMesh(SpawnerFragment->Mesh);
			ItemCooldownMesh->SetStaticMesh(SpawnerFragment->Mesh);
			CooldownNiagaraSystem->SetVariableStaticMesh("Mesh", SpawnerFragment->Mesh);

			ItemMesh->SetRelativeLocation(SpawnerFragment->MeshOffset);
			ItemCooldownMesh->SetRelativeLocation(SpawnerFragment->MeshOffset);
			CooldownNiagaraSystem->SetRelativeLocation(SpawnerFragment->MeshOffset);
		}
	}
}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemSpawner::OnCollision);
}

void AItemSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//CollisionComponent->OnComponentBeginOverlap.RemoveAll(this);
	GetWorld()->GetTimerManager().ClearTimer(ItemCooldownHandle);
}

void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ItemMesh->AddRelativeRotation(FRotator(0, 2.0f, 0));

	if (!bIsItemAvailable)
	{
		float CooldownPercentage =  1 - (GetWorld()->GetTimerManager().GetTimerRemaining(ItemCooldownHandle) / Cooldown);
		CooldownMaterialInstance->SetScalarParameterValue("Percentage", CooldownPercentage);
	}
}

void AItemSpawner::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	Super::OnCollision(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AItemSpawner::AttemptPickup(const AActor* PlayerActor)
{
	Super::AttemptPickup(PlayerActor);
	
	UItemStorageComponent* StorageComponent = Cast<UItemStorageComponent>(PlayerActor->GetComponentByClass(UItemStorageComponent::StaticClass()));
	if (StorageComponent != nullptr && bIsItemAvailable)
	{
		UItemObject* NewItemObject = StorageComponent->GenerateItemObject(ItemData);
		
		if (StorageComponent->AttemptAddItem(NewItemObject))
		{
			GetWorld()->GetTimerManager().SetTimer(ItemCooldownHandle, this, &AItemSpawner::OnCooldownEnded, Cooldown);
			SetItemAvailability(false);
			PlayPickupEffect();
		}
	}
}

void AItemSpawner::PlayPickupEffect_Implementation()
{
	Super::PlayPickupEffect_Implementation();
	
	UItemFragmentPickup* Fragment = ItemData->GetFragmentByClass<UItemFragmentPickup>();

	if (Fragment == nullptr) return;
	
	if (Fragment->PickupVisualEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Fragment->PickupVisualEffect, GetActorLocation());
	}

	if (Fragment->PickupSoundEffect != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Fragment->PickupSoundEffect, GetActorLocation());
	}
}

void AItemSpawner::PlayCooldownEndEffect_Implementation()
{
	
}

void AItemSpawner::CheckExistingOverlap()
{
	Super::CheckExistingOverlap();
}

void AItemSpawner::SetItemAvailability(bool Available)
{
	bIsItemAvailable = Available;
	ItemMesh->SetVisibility(Available);
	ItemCooldownMesh->SetVisibility(!Available);
	ItemMesh->SetRelativeRotation(FRotator(0, -90, 0));
}

void AItemSpawner::OnCooldownEnded()
{
	GetWorld()->GetTimerManager().ClearTimer(ItemCooldownHandle);
	PlayCooldownEndEffect();
	SetItemAvailability(true);
	CheckExistingOverlap();
}
