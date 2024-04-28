// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCInteractive.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"




// Sets default values
ANPCInteractive::ANPCInteractive()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneCOmp"));
	SetRootComponent(SceneComp);
	NPCCam = CreateDefaultSubobject<UCameraComponent>(TEXT("NPCCam"));
	NPCCam->SetupAttachment(SceneComp);
	NPCMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCMesh"));
	NPCMesh->SetupAttachment(SceneComp);
}

// Called when the game starts or when spawned
void ANPCInteractive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

