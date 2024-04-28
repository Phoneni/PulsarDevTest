// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCInteractive.generated.h"

class USceneComponent;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class PULSARDEVTEST_API ANPCInteractive : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPCInteractive();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Dialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPirvateAccess = "true"))
	USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPirvateAccess = "true"))
	UCameraComponent* NPCCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPirvateAccess = "true"))
	USkeletalMeshComponent* NPCMesh;



};
