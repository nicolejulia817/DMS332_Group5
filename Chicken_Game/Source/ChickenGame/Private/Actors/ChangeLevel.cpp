// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ChangeLevel.h"
#include "PlayerChicken.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AChangeLevel::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
	class AActor *OtherActor,
	class UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult &SweepResult) {
// use Super to call version of this func from parent class (Item)
Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex,
bFromSweep, SweepResult);
APlayerChicken *PlayerChicken = Cast<APlayerChicken>(OtherActor);
// check for valid Player
if (PlayerChicken) {
UWorld *TheWorld = GetWorld();

FString CurrentLevel = TheWorld->GetMapName();

if (CurrentLevel == CurrLevel) {

UGameplayStatics::OpenLevel(TheWorld, ToLevel);
} else {
UGameplayStatics::OpenLevel(TheWorld, CurrLevel);
}
}
}