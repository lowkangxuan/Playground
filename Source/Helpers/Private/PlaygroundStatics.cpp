// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundStatics.h"
#include "EnhancedInputSubsystems.h"
#include "Gameplay/PlaygroundGameMode.h"
#include "Gameplay/PlaygroundGameInstance.h"
#include "Player/PlaygroundPlayerController.h"
#include "Player/PlaygroundCharacter.h"
#include "UI/HudManager.h"

bool UPlaygroundStatics::IsWithEditor()
{
#if WITH_EDITOR
	return true;
#else
	return false;
#endif
}

FVector2D UPlaygroundStatics::IndexToGrid(int32 Index, FVector2D GridSize)
{
	return FVector2D(Index % (int)GridSize.X, FMath::Floor(Index / GridSize.X));
}

int32 UPlaygroundStatics::GridToIndex(FVector2D Grid, int32 SizeX)
{
	return Grid.X + (Grid.Y * SizeX);
}

bool UPlaygroundStatics::CheckIfKeyInputsAreSimilar(const UObject* WorldContext, FKey PressedKey, UInputAction* InputAction)
{
	if (WorldContext == nullptr) return false;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(WorldContext->GetWorld()->GetFirstPlayerController()->GetLocalPlayer()))
	{
		const FText InputName = Subsystem->QueryKeysMappedToAction(InputAction)[0].GetDisplayName();
		if (InputName.IdenticalTo(PressedKey.GetDisplayName())) return true;
	}
	return false;
}

FVector2D UPlaygroundStatics::ClampIndividualAxes2D(FVector2D A, float MinX, float MaxX, float MinY, float MaxY)
{
	float X = FMath::Clamp(A.X, MinX, MaxX);
	float Y = FMath::Clamp(A.Y, MinY, MaxY);

	return FVector2D(X, Y);
}

APlaygroundCharacter* UPlaygroundStatics::GetPlaygroundCharacter(const UObject* WorldContext)
{
	APlaygroundPlayerController* PC = GetPlaygroundPlayerController(WorldContext);
	return Cast<APlaygroundCharacter>(PC->GetPawn());
}

APlaygroundPlayerController* UPlaygroundStatics::GetPlaygroundPlayerController(const UObject* WorldContext)
{
	APlaygroundPlayerController* PC = Cast<APlaygroundPlayerController>(WorldContext->GetWorld()->GetFirstPlayerController());
	return WorldContext ? PC : nullptr;
}

APlaygroundGameMode* UPlaygroundStatics::GetPlaygroundGameMode(const UObject* WorldContext)
{
	return WorldContext ? Cast<APlaygroundGameMode>(WorldContext->GetWorld()->GetAuthGameMode()) : nullptr;
}

UPlaygroundGameInstance* UPlaygroundStatics::GetPlaygroundGameInstance(const UObject* WorldContext)
{
	return WorldContext ? Cast<UPlaygroundGameInstance>(WorldContext->GetWorld()->GetGameInstance()) : nullptr;
}

AHudManager* UPlaygroundStatics::GetHudManager(const UObject* WorldContext)
{
	return WorldContext ? Cast<AHudManager>(WorldContext->GetWorld()->GetFirstPlayerController()->MyHUD) : nullptr;
}
