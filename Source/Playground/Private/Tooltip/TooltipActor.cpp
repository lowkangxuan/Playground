// Fill out your copyright notice in the Description page of Project Settings.


#include "Tooltip/TooltipActor.h"
#include "UI/Widgets/UICardWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/Widgets/TooltipWidget.h"


// Sets default values
ATooltipActor::ATooltipActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetDrawSize(FVector2D(400, 150));
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Make sure widget does not collide with anything in the world
	SetRootComponent(WidgetComponent);
}

void ATooltipActor::BeginPlay()
{
	Super::BeginPlay();
	TooltipWidget = Cast<UTooltipWidget>(WidgetComponent->GetWidget());
	//WidgetComponent->InitWidget();
}

void ATooltipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HoveringActor)
	{
		FVector ActorOrigin;
		FVector ActorExtent;
		HoveringActor->GetActorBounds(true, ActorOrigin, ActorExtent);
		SetActorLocation(ActorOrigin + FVector(0, 0, ActorExtent.Z) + Offset);
	}
}

void ATooltipActor::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);
	SetActorTickEnabled(!bNewHidden); // Disable ticking based on whether or not the actor is currently hidden in-game
}

void ATooltipActor::SetTooltipInfo(const UTexture2D* ItemIcon, const FText& ItemName, const FText& ItemDesc)
{
	TooltipWidget->UpdateInfo(ItemIcon, ItemName, ItemDesc);
}

