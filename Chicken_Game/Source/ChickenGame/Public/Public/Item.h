// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"
// forward declarations
class UStaticMeshComponent;
class USphereComponent;
// REMEMBER to change the name of the API
// if your project is not named Class
UCLASS()
class CHICKENGAME_API AItem : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AItem();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // NEW!!!

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
  float Amplitude = 0.25f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
  float TimeConstant = 5.f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float RotationRate = 40.f;
  // add 'virtual' to these so they can be customized in child classes
  UFUNCTION()
  virtual void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult);

  UFUNCTION()
  virtual void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                            class AActor *OtherActor,
                            class UPrimitiveComponent *OtherComp,
                            int32 OtherBodyIndex);

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UStaticMeshComponent *ItemMesh;

  /** sphere component */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  class USphereComponent *Sphere;

private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
            meta = (AllowPrivateAccess = "true"))
  float RunningTime;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
            meta = (AllowPrivateAccess = "true"))
  float PerlinValue;

  // end NEW

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
};