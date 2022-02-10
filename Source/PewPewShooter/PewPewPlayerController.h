// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PewPewPlayerController.generated.h"


UCLASS()
class PEWPEWSHOOTER_API APewPewPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* HUDRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* CrosshairRef;

protected:
	virtual void BeginPlay() override;

private:

	// Creating the button to pick a lose screen in bp_pewpewplayercontroller
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;


	UPROPERTY(EditAnywhere)
		float RestartDelay = 3;


	FTimerHandle RestartTimer;
};
