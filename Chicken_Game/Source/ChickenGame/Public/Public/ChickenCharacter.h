// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
// add this
#include "InputActionValue.h"
#include "ChickenCharacter.generated.h"

// add these
// forward declarations
// mapping context and action for enh input
class UInputMappingContext;
class UInputAction;
// arm and camera
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CHICKENGAME_API AChickenCharacter : public ACharacter {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AChickenCharacter();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
  // add these - note names of mapping context
  UPROPERTY(EditAnywhere, Category = Input)
  UInputMappingContext *ClassContext;

  UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Hat")
  bool HasHat = false;



  UPROPERTY(EditAnywhere, Category = Input)
  UInputAction *MovementAction;

  void Move(const FInputActionValue &Value);

  UPROPERTY(EditAnywhere, Category = Input)
  UInputAction *LookAction;

  void Look(const FInputActionValue &Value);

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

  // add these
private:
  // jump input action
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
            meta = (AllowPrivateAccess = "true"))
  UInputAction *JumpAction;
  // end jump input action
  UPROPERTY(VisibleAnywhere)
  USpringArmComponent *CameraBoom;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent *ViewCamera;
};