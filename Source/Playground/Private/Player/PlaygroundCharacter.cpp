// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/PlaygroundCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/DecalComponent.h"
#include "Components/DamageableComponent.h"
#include "Components/ItemStorageComponent.h"
#include "Interfaces/CursorInteractionInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	CursorDecal = CreateDefaultSubobject<UDecalComponent>("Cursor Decal");
	CursorDecal->SetupAttachment(RootComponent);
	CursorDecal->SetRelativeRotation(FRotator(90, 0, 0));
	CursorDecal->DecalSize = FVector(16, 32, 32);

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
	AddOwnedComponent(DamageableComponent);

	InventoryComponent = CreateDefaultSubobject<UItemStorageComponent>(TEXT("Inventory"));
	AddOwnedComponent(InventoryComponent);

	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	AddOwnedComponent(PhysicsHandleComponent);
}

void APlaygroundCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			Subsystem->AddMappingContext(UIMappingContext, 0);
		}
	}
}

void APlaygroundCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MouseToWorld();
}

void APlaygroundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::Look);

#if WITH_EDITORONLY_DATA
		EnhancedInputComponent->BindAction(CheatConsoleAction, ETriggerEvent::Started, this, &APlaygroundCharacter::ToggleCheatConsole);
#endif

		EnhancedInputComponent->BindAction(LeftMouseBtnAction, ETriggerEvent::Started, this, &APlaygroundCharacter::HandleLeftClick);
		EnhancedInputComponent->BindAction(ObjectRotateAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::RotateItem);
		
		EnhancedInputComponent->BindAction(RightMouseBtnAction, ETriggerEvent::Triggered, this, &APlaygroundCharacter::EnableLook);
		EnhancedInputComponent->BindAction(RightMouseBtnAction, ETriggerEvent::Completed, this, &APlaygroundCharacter::DisableLook);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlaygroundCharacter::MouseToWorld()
{
	FHitResult OutResult;
	FVector RayStart;
	FVector RayDir;
	FCollisionQueryParams RayParams;
	RayParams.AddIgnoredActor(bIsGrabbingItem ? GrabbedActor : nullptr);
	
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(RayStart, RayDir);
	GetWorld()->LineTraceSingleByChannel(OutResult, RayStart, RayStart + (RayDir * 1500), ECC_Visibility, RayParams);
	
	RayEndLocation = OutResult.bBlockingHit ? OutResult.Location : OutResult.TraceEnd;
	CursorDecal->SetWorldLocation(RayEndLocation);
	if (OutResult.GetActor()) { CursorDecal->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(OutResult.ImpactNormal)); }
	
	bCanGrabItem = IsValid(OutResult.GetActor()) && OutResult.GetActor()->GetClass()->ImplementsInterface(UCursorInteractionInterface::StaticClass()) && !bIsGrabbingItem;

	if (IsValid(OutResult.GetComponent()) && IsValid(OutResult.GetComponent()->GetAttachParent()) && OutResult.GetComponent()->GetAttachParent()->GetClass()->ImplementsInterface(UCursorInteractionInterface::StaticClass()))
	{
		GrabbedComponent = OutResult.GetComponent();
		ICursorInteractionInterface::Execute_OnCursorEnter(GrabbedComponent->GetAttachParent());
		HideCursorDecal();
	}
	else
	{
		if (IsValid(GrabbedComponent))
		{
			ICursorInteractionInterface::Execute_OnCursorExit(GrabbedComponent->GetAttachParent());
		}
		GrabbedComponent = nullptr;
		ShowCursorDecal();
	}
	
	if (bCanGrabItem)
	{
		// Turn off highlight when changing target actor 
		if (IsValid(GrabbedActor) && GrabbedActor != OutResult.GetActor()) ICursorInteractionInterface::Execute_OnCursorExit(GrabbedActor);
		GrabbedActor = OutResult.GetActor();
		ICursorInteractionInterface::Execute_OnCursorEnter(GrabbedActor);
		HideCursorDecal();
	}
	else if (IsValid(GrabbedActor) && !bIsGrabbingItem)
	{
		ICursorInteractionInterface::Execute_OnCursorExit(GrabbedActor);
		GrabbedActor = nullptr;
		ShowCursorDecal();
	}

	// Handling grabbed actor
	if (bIsGrabbingItem)
	{
		PhysicsHandleComponent->SetTargetLocation(RayEndLocation + FVector(0, 0, 150));
		PhysicsHandleComponent->GetGrabbedComponent()->SetPhysicsAngularVelocityInDegrees(FVector(0)); // Prevents the grabbed component from rotating out of control
	}
}

#if WITH_EDITOR
void APlaygroundCharacter::ToggleCheatConsole_Implementation()
{
}
#endif

void APlaygroundCharacter::HandleLeftClick()
{
	if (IsValid(GrabbedActor)) ICursorInteractionInterface::Execute_OnMouseClicked(GrabbedActor);
	if (IsValid(GrabbedComponent) && GrabbedComponent->GetAttachParent()->GetClass()->ImplementsInterface(UCursorInteractionInterface::StaticClass()))
	{
		ICursorInteractionInterface::Execute_OnMouseClicked(GrabbedComponent->GetAttachParent());
		return;
	}
	
	if (bCanGrabItem) // Grabbing item
	{
		bIsGrabbingItem = true;
		bCanGrabItem = false;
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(Cast<UPrimitiveComponent>(GrabbedActor->GetRootComponent()), NAME_None, GrabbedActor->GetActorLocation(), GrabbedActor->GetActorRotation());
		PhysicsHandleComponent->SetTargetRotation(FRotator(0, FMath::RoundHalfToEven(GrabbedActor->GetActorRotation().Yaw /90) * 90, 0));
	}
	else if (bIsGrabbingItem) // Releasing item
	{
		bIsGrabbingItem = false;
		PhysicsHandleComponent->ReleaseComponent();
		ICursorInteractionInterface::Execute_ConstraintPhysics(GrabbedActor);
		GrabbedActor = nullptr;
	}
}

void APlaygroundCharacter::RotateItem(const FInputActionValue& Value)
{
	if (!bIsGrabbingItem) return;
	
	FVector ItemLocation;
	FRotator ItemRotation;
	PhysicsHandleComponent->GetTargetLocationAndRotation(ItemLocation, ItemRotation);
	ItemRotation += FRotator(0, Value.Get<float>() * 120, 0);
	PhysicsHandleComponent->SetTargetRotation(ItemRotation);
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

void APlaygroundCharacter::ShowCursorDecal()
{
	CursorDecal->SetVisibility(true);
}

void APlaygroundCharacter::HideCursorDecal()
{
	CursorDecal->SetVisibility(false);
}
