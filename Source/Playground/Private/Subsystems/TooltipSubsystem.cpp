// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TooltipSubsystem.h"

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
	}
}

void UTooltipSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
