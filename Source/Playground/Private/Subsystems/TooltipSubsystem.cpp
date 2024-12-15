// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TooltipSubsystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Items/ItemDataAsset.h"
#include "Tooltip/TooltipActor.h"

UTooltipSubsystem::UTooltipSubsystem()
{
	static ConstructorHelpers::FClassFinder<AActor> TooltipActorClass(TEXT("/Game/Blueprints/Tooltips/TooltipActor"));
	if (TooltipActorClass.Class != NULL) ActorClass = TooltipActorClass.Class;
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

void UTooltipSubsystem::ShowTooltip(const UItemDataAsset* Data, const FVector& WorldLocation, float InteractionDelay)
{
	//UE_LOG(LogTemp, Log, TEXT("%s"), IsValid(TooltipActor) ? TEXT("true") : TEXT("false"));
	if (TooltipActor == nullptr)
	{
		SpawnTooltipActor();
	}
	
	if (Data && IsValid(TooltipActor))
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *Data->DisplayName.ToString());
		TooltipActor->SetActorLocation(WorldLocation);
		TooltipActor->SetActorHiddenInGame(false);
	}
}

void UTooltipSubsystem::HideTooltip()
{
	if (TooltipActor) TooltipActor->SetActorHiddenInGame(true);
}

void UTooltipSubsystem::SpawnTooltipActor()
{
	if (ActorClass != nullptr)
	{
		TooltipActor = GetWorld()->SpawnActor<ATooltipActor>(ActorClass, FVector(0, 0, -10000), FRotator(0, 0, 0));
		TooltipActor->SetActorHiddenInGame(true);
	}
}
