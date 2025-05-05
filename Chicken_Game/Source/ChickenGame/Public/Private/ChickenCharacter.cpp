// Fill out your copyright notice in the Description page of Project Settings.


#include "ChickenCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// for arm and cam
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// for GetCharacterMovement() below
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AChickenCharacter::AChickenCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  // add these
  // different from pawn movement
  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  bUseControllerRotationRoll = false;

  GetCharacterMovement()->bOrientRotationToMovement = true;
  // Character moves in the direction of input...
  GetCharacterMovement()->RotationRate =
      FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

  // Create a camera boom (pulls in towards the player if there is a collision)
  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(GetRootComponent());
  CameraBoom->TargetArmLength =
      400.0f; // The camera follows at this distance behind the character
  CameraBoom->bUsePawnControlRotation =
      true; // Rotate the arm based on the controller
  // Create a follow camera
  ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
  ViewCamera->SetupAttachment(CameraBoom);
  ViewCamera->bUsePawnControlRotation =
      false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void AChickenCharacter::BeginPlay() {
  Super::BeginPlay();
  // add this
  // Add Input Mapping Context
  if (APlayerController *PlayerController =
          Cast<APlayerController>(GetController())) {
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(ClassContext, 0);
    }
  }
}

//  add these
void AChickenCharacter::Move(const FInputActionValue &Value) {
  // use the direction keys (w a s d) AND the mouse orientation
  const FVector2D MovementVector = Value.Get<FVector2d>();
  const FRotator Rotation = Controller->GetControlRotation();
  const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
  const FVector ForwardDirection =
      FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
  AddMovementInput(ForwardDirection, MovementVector.Y);
  const FVector RightDirection =
      FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
  AddMovementInput(RightDirection, MovementVector.X);
}
// add these
void AChickenCharacter::Look(const FInputActionValue &Value) {
  // input is a Vector2D
  FVector2D LookAxisVector = Value.Get<FVector2D>();

  if (Controller != nullptr) // protection
  {
    // add yaw and pitch input to controller
    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
  }
}

// Called every frame
void AChickenCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void AChickenCharacter::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  // add these
  // Set up action bindings
  if (UEnhancedInputComponent *EnhancedInputComponent =
          Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
    EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered,
                                       this, &AChickenCharacter::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
                                       this, &AChickenCharacter::Look);
    //  jumping
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
                                       &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
                                       this, &ACharacter::StopJumping);
    // end jumping
  }
}