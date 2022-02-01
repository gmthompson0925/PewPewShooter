// Fill out your copyright notice in the Description page of Project Settings.


#include "PewPewThing.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APewPewThing::APewPewThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// setup root component for bp_pewpewthing
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// setup the mesh component for the bp_pewpewthing
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// method to pull gun trigger
void APewPewThing::PullTrigger()
{
	// Ammo system
	if (LoadedAmmo <= 0)
	{
		// play empty clip sound
		return;
	}
	else
	{
		LoadedAmmo = LoadedAmmo - 1;
	}

	// spawning particle effect off of the muzzle socket of the gun
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	// spawning muzzle sound wave off of muzzle socket
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));


	// adding Hit result and direction vector for parameters
	FHitResult Hit;
	FVector ShotDirection;

	// initializing bSuccessHit to track if a successful hit using GunTrace method
	bool bSuccessHit = GunTrace(Hit, ShotDirection);


	if (bSuccessHit)
	{
		// Creating gun shot particle effect at hit location using hit and shotdirection params
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

		// Creating impact sound on Hit location
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		// initializing an actor that has been hit by shot
		AActor* HitActor = Hit.GetActor();

		// if it is not a nullptr, then:
		if (HitActor != nullptr)
		{
			// call a FPointDamagEevent with a damage var and hit and shotdirection
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

			// initializing a controller parameter to add to TakeDamage function
			AController* OwnerController = GetOwnerController();

			// Using HitActor pointer with arrow to call a TakeDamage function, utilizing previous lines as params
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// method to reload gun
void APewPewThing::OnReload()
{
	// Is there Ammo in the pool?
	if (AmmoPool <= 0 || LoadedAmmo >= 30)
	{
		return;
	}

	// Check if we need ammo from the pool and load the gun
	if (AmmoPool < (15 - LoadedAmmo))
	{
		LoadedAmmo = LoadedAmmo + AmmoPool;
		AmmoPool = 0;
	}
	// Otherwise, update the ammo pool
	else
	{
		AmmoPool = AmmoPool - (15 - LoadedAmmo);
		LoadedAmmo = 15;
	}
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

// Creating GunTrace method to LineTrace to an actor to register hit
bool APewPewThing::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	// Initializing owner controller to do a nullptr check
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;

	
	FVector Location;
	FRotator Rotation;

	// Using OwnerController to set player's Line of sight through the camera
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	// Adding end range for the line trace
	FVector End = Location + Rotation.Vector() * MaxRange;

	// Creating params to ingore actors so they don't shoot themselves and stop shooting after death
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	// return LineTrace with proper parameters to the method
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

// Method to get owning controller
AController* APewPewThing::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}

