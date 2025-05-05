// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelChange.h"
#include "ChickenCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
// check it out
// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Engine/Kismet/UGameplayStatics/OpenLevel

void ALevelChange::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                                  class AActor *OtherActor,
                                  class UPrimitiveComponent *OtherComp,
                                  int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult &SweepResult) {
  // use Super to call version of this func from parent class (Item)
  Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex,
                        bFromSweep, SweepResult);
  // cast from MyCharacter class so we can move the character
  AChickenCharacter *ChickenCharacter = Cast<AChickenCharacter>(OtherActor);
  // check for valid Character
  if (ChickenCharacter) {
    UWorld *TheWorld = GetWorld();

    FString CurrentLevel = TheWorld->GetMapName();

    if (CurrentLevel == CurrLevel) {

      UGameplayStatics::OpenLevel(TheWorld, ToLevel);
    } else {
      UGameplayStatics::OpenLevel(TheWorld, CurrLevel);
    }
  }
}