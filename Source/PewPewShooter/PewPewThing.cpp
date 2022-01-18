// Fill out your copyright notice in the Description page of Project Settings.


#include "PewPewThing.h"
#include "Components/SkeletalMeshComponent.h"
// Sets default values
APewPewThing::APewPewThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void APewPewThing::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You have been shot."));
}

// Called when the game starts or when spawned
void APewPewThing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APewPewThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

