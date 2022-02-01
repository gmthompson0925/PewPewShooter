// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCrate.h"
#include "PewPewThing.h"
#include "PewPewGuy.h"

// Sets default values
AAmmoCrate::AAmmoCrate()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	count = 15;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AAmmoCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoCrate::OnPickup(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	APewPewGuy* Guy = Cast<APewPewGuy>(OtherActor);

	if (Guy != nullptr)
	{
		
	}
}


