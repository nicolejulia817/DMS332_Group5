// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChangeLevel.generated.h"

UCLASS()
class CHICKENGAME_API AChangeLevel : public AItem {
  GENERATED_BODY()
protected:
  // redeclare functions as overrides from the parent versions in Item.h
  // can't use UFUNCTION here because they're already declared in Item.h
  // UFUNCTION()
  virtual void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult) override;
// properties so we can assign different levels in BP child class
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Parameters")
FName CurrLevel;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Parameters")
FName ToLevel;

};
