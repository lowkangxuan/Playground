// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PlaygroundGameMode.h"

void APlaygroundGameMode::SetInputModeAndPauseState(EInputModes InputMode, bool bSetGamePause)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	switch (InputMode)
	{
		case EInputModes::OnlyGame :
			{
				FInputModeGameOnly Mode;
				Mode.SetConsumeCaptureMouseDown(false);
				PlayerController->SetInputMode(Mode);
				break;
			}

	case EInputModes::OnlyUI :
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				//PlayerController->SetShowMouseCursor(true);
				break;
			}

	case EInputModes::GameAndUI :
			{
				PlayerController->SetInputMode(FInputModeGameAndUI());
				break;
			}
	}
	
	PlayerController->SetPause(bSetGamePause);
}
