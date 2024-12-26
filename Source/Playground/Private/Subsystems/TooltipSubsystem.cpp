// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TooltipSubsystem.h"

#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Structs/TooltipInfo.h"
#include "Items/ItemDataAsset.h"
#include "Tooltip/TooltipActor.h"
#include "UI/Widgets/TooltipWidget.h"

UTooltipSubsystem::UTooltipSubsystem()
{
	// Getting TooltipActor BP Class
	static ConstructorHelpers::FClassFinder<AActor> TooltipActorClass(TEXT("/Game/Blueprints/Tooltips/TooltipActor"));
	if (TooltipActorClass.Class != nullptr) TooltipClass = TooltipActorClass.Class;
}

bool UTooltipSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UTooltipSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTooltipSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTooltipSubsystem::SpawnTooltipActor()
{
	TooltipActor = GetWorld()->SpawnActor<ATooltipActor>(TooltipClass, FVector(0, 0, 0), FRotator(0, 0, 0));
	checkf(TooltipActor, TEXT("Tooltip Actor is somehow not spawned in the Subsystem!!!"));
	TooltipWidget = Cast<UTooltipWidget>(TooltipActor->WidgetComponent->GetWidget());
	HideTooltip();
}

void UTooltipSubsystem::ShowTooltip(const UItemDataAsset* Data, AActor* ItemActor, const FVector& SpawnOffset, float InteractionDelay)
{
	if (Data == nullptr) return; // No data to display, have to provide an ItemData from the Interactable Component
	if (TooltipActor == nullptr)
	{
		SpawnTooltipActor();
	}

	TooltipWidget->UpdateInfo(FTooltipInfo(Data->Icon, Data->Name, Data->SubTitle, Data->Description, InteractionDelay));
	TooltipActor->HoveringActor = ItemActor;
	TooltipActor->Offset = SpawnOffset;
	TooltipActor->SetActorHiddenInGame(false);
}

void UTooltipSubsystem::HideTooltip()
{
	if (TooltipActor) TooltipActor->SetActorHiddenInGame(true);
}

void UTooltipSubsystem::InputTime(float Time)
{
	TooltipWidget->UpdateInputElapsedTime(Time);
}

void UTooltipSubsystem::InputCancelled()
{
	TooltipWidget->UpdateInputElapsedTime(0.0f);
}


