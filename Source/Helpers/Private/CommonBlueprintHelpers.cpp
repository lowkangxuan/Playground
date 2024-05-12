// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonBlueprintHelpers.h"
#include "Gameplay/PlaygroundGameMode.h"
#include "Gameplay/PlaygroundGameInstance.h"
#include "EnhancedInputSubsystems.h"

bool UCommonBlueprintHelpers::IsWithEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}

FVector2D UCommonBlueprintHelpers::IndexToGrid(int32 Index, FVector2D GridSize)
{
	return FVector2D(Index % (int)GridSize.X, FMath::Floor(Index / GridSize.X));
}

int32 UCommonBlueprintHelpers::GridToIndex(FVector2D Grid, int32 SizeY)
{
	return Grid.X + (Grid.Y * SizeY);
}

bool UCommonBlueprintHelpers::CheckIfKeyInputsAreSimilar(const UObject* WorldContext, FKey PressedKey, UInputAction* InputAction)
{
	if (WorldContext == nullptr) return false;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(WorldContext->GetWorld()->GetFirstPlayerController()->GetLocalPlayer()))
	{
		const FText InputName = Subsystem->QueryKeysMappedToAction(InputAction)[0].GetDisplayName();
		if (InputName.IdenticalTo(PressedKey.GetDisplayName())) return true;
	}
	return false;
}

APlaygroundGameMode* UCommonBlueprintHelpers::GetPlaygroundGameMode(const UObject* WorldContext, bool& bSuccess)
{
	if (WorldContext)
	{
		bSuccess = true;
		return Cast<APlaygroundGameMode>(WorldContext->GetWorld()->GetAuthGameMode());
	}

	bSuccess = false;
	return nullptr;
}

UPlaygroundGameInstance* UCommonBlueprintHelpers::GetPlaygroundGameInstance(const UObject* WorldContext, bool& bSuccess)
{
	if (WorldContext)
	{
		bSuccess = true;
		return Cast<UPlaygroundGameInstance>(WorldContext->GetWorld()->GetGameInstance());
	}

	bSuccess = false;
	return nullptr;
}
