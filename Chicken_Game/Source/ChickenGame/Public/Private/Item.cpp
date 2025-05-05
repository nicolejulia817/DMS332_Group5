// Fill out your copyright notice in the Description page of Project Settings.
// Perlin1D
// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Math/FMath/PerlinNoise1D?application_version=5.5

#include "Item.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h" // for Perlin & sin

// Sets default values
AItem::AItem() {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  // create static mesh and set it as root component
  ItemMesh =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
  RootComponent = ItemMesh;
  // create sphere for overlap and attach it to root component
  Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
  Sphere->InitSphereRadius(150.0f);
  Sphere->SetupAttachment(RootComponent);
  // set up a notification for when this component
  // overlaps something
  Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);

  Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}
// Called when the game starts or when spawned
void AItem::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AItem::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

  float MovementRate = 50.f;
  // float RotationRate = 40.f;
  //    AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
  AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
  // RunningTime defined in Item.h
  RunningTime += DeltaTime;
  PerlinValue = FMath::PerlinNoise1D(RunningTime);
  float SineValue = Amplitude * FMath::Sin(RunningTime * TimeConstant);
  AddActorWorldOffset(FVector(0.f, 0.f, SineValue));
  if (GEngine) {
    // FString Name = GetName();
    // FString Message = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);
    // FString Message = FString::Printf(TEXT("RunningTime: %f"), RunningTime);
    // FString Message = FString::Printf(TEXT("PerlinValue: %f"), PerlinValue);
    // GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, Message);
  }
  // end NEW
}
void AItem::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                           class AActor *OtherActor,
                           class UPrimitiveComponent *OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep,
                           const FHitResult &SweepResult) {
  if (OtherActor && (OtherActor != this) && OtherComp) {
    // put code to execute on overlap begin here
    const FString OtherActorName = OtherActor->GetName();
    if (GEngine) {
      GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, OtherActorName);
    }
  }
}

void AItem::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                         class AActor *OtherActor,
                         class UPrimitiveComponent *OtherComp,
                         int32 OtherBodyIndex) {
  if (OtherActor && (OtherActor != this) && OtherComp) {
    // put code to execute on overlap end here
  }
}