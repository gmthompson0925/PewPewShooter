// Fill out your copyright notice in the Description page of Project Settings.


#include "PewPewAIController.h"
#include "Kismet/GameplayStatics.h"

void APewPewAIController::BeginPlay()
{
	Super::BeginPlay();
}

void APewPewAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (LineOfSightTo(PlayerPawn))
	{
		MoveToActor(PlayerPawn, SightRadius);
		SetFocus(PlayerPawn);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}

