// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PulsarWorldSubSystem.generated.h"

UCLASS()
class PULSARDEVTEST_API UPulsarWorldSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> Units;
	UPROPERTY(BlueprintReadOnly)
	AActor* MapCameraActor;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterUnit(AActor* InUnit);
	UFUNCTION(BlueprintCallable)
	void UnregisterUnit(AActor* InUnit);
	UFUNCTION(BlueprintCallable)
	void RegisterMapCameraActor(AActor* InCameraActor);

	void SetUnitsHidden(bool bHidden);
};
