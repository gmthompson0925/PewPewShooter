// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PewPewGuy.generated.h"

UCLASS()
class PEWPEWSHOOTER_API APewPewGuy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APewPewGuy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	// Alternate way of creating the look up movement function
	// void LookUp(float AxisValue);

};
