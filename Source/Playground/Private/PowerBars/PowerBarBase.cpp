// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerBars/PowerBarBase.h"


// Sets default values
APowerBarBase::APowerBarBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APowerBarBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerBarBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

