// Fill out your copyright notice in the Description page of Project Settings.


#include "PewPewAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PewPewGuy.h"

void APewPewAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void APewPewAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool APewPewAIController::IsDead() const
{
	APewPewGuy* ControlledCharacter = Cast<APewPewGuy>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}

