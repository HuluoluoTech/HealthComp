// Copyright Epic Games, Inc. All Rights Reserved.

#include "HealthCompCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "FireEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

//////////////////////////////////////////////////////////////////////////
// AHealthCompCharacter

AHealthCompCharacter::AHealthCompCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHealthCompCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHealthCompCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHealthCompCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AHealthCompCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AHealthCompCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHealthCompCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHealthCompCharacter::TouchStopped);

	//Bind OnDamagePressed Action Event
	PlayerInputComponent->BindAction("OnDamagePressed", IE_Pressed, this, &AHealthCompCharacter::DamagePlayerCharacter);

	PlayerInputComponent->BindAction("FindActorPressed", IE_Pressed, this, &AHealthCompCharacter::OnFindActorPressed);


}

void AHealthCompCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AHealthCompCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AHealthCompCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHealthCompCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHealthCompCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHealthCompCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AHealthCompCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthChanged.AddDynamic(this, &AHealthCompCharacter::OnHealthChanged);
}

void AHealthCompCharacter::OnHealthChanged(UHealthComponent* HealthComp, float Health, float DamageAmount, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("The Player's Current Health is: %f"), Health);
}

void AHealthCompCharacter::DamagePlayerCharacter()
{
	// 执行Damage操作，监听 OnTakeAnyDamege 的Component会收到通知；此处是 HealthComponent 会收到。
	UGameplayStatics::ApplyDamage(this, 20.0f, GetInstigatorController(), this, GenericDamageType);
}

void AHealthCompCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (IInteractInterface* ActorCheck = Cast<IInteractInterface>(OtherActor))
	{
		ActorCheck->OnInteract();
	}
}

void AHealthCompCharacter::OnFindActorPressed()
{
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFireEffect::StaticClass(), ActorsToFind);
		UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AFireEffect::StaticClass(), FName("FindActorTag"), ActorsToFind);
	}

	for (AActor* FireEffectActor : ActorsToFind)
	{
		//Is this Actor of type FireEffect class?
		AFireEffect* FireEffectCast = Cast<AFireEffect>(FireEffectActor);
		if (FireEffectCast)
		{
			//Get the Particle Fire Component and deactivate it.            
			FireEffectCast->GetParticleFireComponent()->Deactivate();

			//Get the Fire Audio Component and deactivate it.           
			FireEffectCast->GetFireAudioComponent()->Deactivate();
		}
	}
}
