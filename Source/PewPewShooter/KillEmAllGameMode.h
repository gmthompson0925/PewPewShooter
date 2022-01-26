// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PewPewShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"


UCLASS()
class PEWPEWSHOOTER_API AKillEmAllGameMode : public APewPewShooterGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
