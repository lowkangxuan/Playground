// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PhysicalItem.h"


// Sets default values
APhysicalItem::APhysicalItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	RootMesh->SetSimulatePhysics(true);
	
	SetRootComponent(RootMesh);
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

