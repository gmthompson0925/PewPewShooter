// Fill out your copyright notice in the Description page of Project Settings.


#include "PewPewGuy.h"
#include "PewPewThing.h"
#include "Components/CapsuleComponent.h"
#include "PewPewShooterGameModeBase.h"

// Sets default values
APewPewGuy::APewPewGuy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APewPewGuy::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	// Spawing the player actor
	PewPew = GetWorld()->SpawnActor<APewPewThing>(PewPewClass);

	// Hiding the weapon socket mesh that was buggy
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// Creating and attatching a new weapon socket for the player to hold the gun
	PewPew->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	PewPew->SetOwner(this);
}

// Called every frame
void APewPewGuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APewPewGuy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APewPewGuy::MoveForward);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APewPewGuy::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APewPewGuy::LookUpRate);

	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APewPewGuy::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APewPewGuy::Shoot);

}

// Method to take damage
float APewPewGuy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// set damge cap to not go past zero into the negatives
	DamageToApply = FMath::Min(Health, DamageToApply);

	// Take damage from health
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);
	
	if (IsDead())
	{
		// Getting the pointer to the default game mode
		APewPewShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<APewPewShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			// with the default GameMode, call Pawn Killed to be this actor
			GameMode->PawnKilled(this);
		}

		// Disconnect Player controller to prevent movement upon dying
		DetachFromControllerPendingDestroy();

		// Allows Player to walk over dead AI
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Return damge to be taken!!!
	return DamageToApply;
}

// Quick method to declare if health is less than 0
bool APewPewGuy::IsDead() const
{
		return Health <=0;
}

// Turning the health from float to a percentage for the health bar
float APewPewGuy::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void APewPewGuy::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APewPewGuy::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}


// For rates, making sure to multiply by delta to stay consistent with frame rate
void APewPewGuy::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APewPewGuy::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

// Using the spawned actor to shoot the trigger
void APewPewGuy::Shoot()
{
	PewPew->PullTrigger();
}
