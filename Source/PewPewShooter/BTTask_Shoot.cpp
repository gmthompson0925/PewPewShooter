// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "PewPewGuy.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APewPewGuy* Guy = Cast<APewPewGuy>(OwnerComp.GetAIOwner()->GetPawn());

	if (Guy == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Guy->Shoot();

	return EBTNodeResult::Succeeded;
}