// Fill out your copyright notice in the Description page of Project Settings.

#include "Hat.h"
// need to include header for ChickenCharacter because we're attaching
// this to a socket on its skeletal mesh
#include "ChickenCharacter.h"

void AHat::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult) {
  // use Super to call version of this func from parent class (Item)
  Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex,
                        bFromSweep, SweepResult);
  // cast from ChickenCharacter class so we can attach this to its socket
  AChickenCharacter *ChickenCharacter = Cast<AChickenCharacter>(OtherActor);
  // check for valid Character
  if (ChickenCharacter) {
    // assign transform rules for attachment
    FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,
                                             TRUE);
    // do the attachment
    ItemMesh->AttachToComponent(ChickenCharacter->GetMesh(), TransformRules,
                                FName("scullSocket"));
                                ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    RotationRate = 0;
    // experiment
    EquippedState = true;
  }
}

void AHat::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                            class AActor *OtherActor,
                            class UPrimitiveComponent *OtherComp,
                            int32 OtherBodyIndex) {
  Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}