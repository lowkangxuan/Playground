// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TooltipSubsystem.h"

#include "Items/ItemDataAsset.h"
#include "Tooltip/TooltipActor.h"

bool UTooltipSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return true;
}

void UTooltipSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (!TooltipActor)
	{
		TooltipActor = GetWorld()->SpawnActor<ATooltipActor>(ATooltipActor::StaticClass(), FTransform::Identity);
		TooltipActor->SetActorHiddenInGame(true);
	}
}

void UTooltipSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTooltipSubsystem::ShowTooltip(const UItemDataAsset* Data, float InteractionDelay)
{
	if (Data) UE_LOG(LogTemp, Log, TEXT("%s"), *Data->DisplayName.ToString());
}
