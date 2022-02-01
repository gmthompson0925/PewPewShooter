// Fill out your copyright notice in the Description page of Project Settings.


#include "PewPewPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

// On begin play, we call our refrences to the widgets and add them to the viewport
void APewPewPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void APewPewPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	// Always call Super for overriden classes!!!
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// Remove HUD widget once GameHasEnded has been called
	HUD->RemoveFromViewport();

	// if we won,
	if (bIsWinner)
	{
		// creating WinScreen pointer and intializing as CreateWidget using the UPROPERTY we set up in header file
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

		// check for nullptr and if not,
		if (WinScreen != nullptr)
		{
			// We can add to viewport
			WinScreen->AddToViewport();
		}
	}
	// if we lose, do the same process for our losescreen widget
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}
	
	// Creating a timer to restart the level after the win/lose conditions are met
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
