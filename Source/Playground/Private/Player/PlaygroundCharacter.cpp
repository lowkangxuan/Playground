// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/PlaygroundCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Player/PlaygroundPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/DamageableComponent.h"
#include "Components/ItemStorageComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APlaygroundCharacter

APlaygroundCharacter::APlaygroundCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
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
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

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

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
	AddOwnedComponent(DamageableComponent);

	InventoryComponent = CreateDefaultSubobject<UItemStorageComponent>(TEXT("Inventory"));
	AddOwnedComponent(InventoryComponent);
}

void APlaygroundCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlaygroundCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlaygroundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		APlaygroundPlayerController* PC = Cast<APlaygroundPlayerController>(GetWorld()->GetFirstPlayerController());
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::Look);
	
		Input->BindAction(LeftMouseBtnAction, ETriggerEvent::Started, PC, &APlaygroundPlayerController::InteractWithWorld);
		Input->BindAction(ObjectRotateAction, ETriggerEvent::Triggered, PC, &APlaygroundPlayerController::RotateHandle);
		Input->BindAction(InteractAction, ETriggerEvent::Triggered, PC, &APlaygroundPlayerController::InteractWithItem);
		Input->BindAction(InteractAction, ETriggerEvent::Completed, PC, &APlaygroundPlayerController::InteractCancelled);

		Input->BindAction(RightMouseBtnAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::EnableLook);
		Input->BindAction(RightMouseBtnAction, ETriggerEvent::Completed, this, &APlaygroundCharacter::DisableLook);

#if WITH_EDITORONLY_DATA
		Input->BindAction(CheatConsoleAction, ETriggerEvent::Started, this, &APlaygroundCharacter::ToggleCheatConsole);
#endif
	}
}

void APlaygroundCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void APlaygroundCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr && bCanLook)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlaygroundCharacter::EnableLook()
{
	bCanLook = true;
}

void APlaygroundCharacter::DisableLook()
{
	bCanLook = false;
}

#if WITH_EDITOR
void APlaygroundCharacter::ToggleCheatConsole_Implementation()
{
}
#endif