// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PhysicalItem.h"


// Sets default values
APhysicalItem::APhysicalItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetCollisionProfileName("PhysicalItem");
	RootMesh->BodyInstance.bLockXRotation = true;
	RootMesh->BodyInstance.bLockYRotation = true;
	RootMesh->BodyInstance.bLockZRotation = true;
	//RootMesh->BodyInstance.SetDOFLock(EDOFMode::SixDOF);
	
	RootComponent = RootMesh;
}

// Called when the game starts or when spawned
void APhysicalItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicalItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicalItem::SetPickedup(bool bPickedup)
{
	if (bPickedup)
	{
		RootMesh->SetCollisionProfileName("PhysicalItemPicked");
	}
	else
	{
		RootMesh->SetCollisionProfileName("PhysicalItem");
	}
}

void APhysicalItem::ConstraintVelocity()
{
	const FVector ActorVelocity = GetVelocity();
	RootMesh->AddImpulse(FVector(ActorVelocity.X * -1, ActorVelocity.Y * -1, (ActorVelocity.Z > 0 ? ActorVelocity.Z * -1: 0)), NAME_None, true);
}

