// Fill out your copyright notice in the Description page of Project Settings.


#include "Tooltip/TooltipActor.h"
#include "UI/Widgets/TooltipCard.h"
#include "Components/WidgetComponent.h"


// Sets default values
ATooltipActor::ATooltipActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	SetRootComponent(WidgetComponent);
}

// Called when the game starts or when spawned
void ATooltipActor::BeginPlay()
{
	Super::BeginPlay();
	WidgetComponent->InitWidget();
}

// Called every frame
void ATooltipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

