// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAI.generated.h"


class AUnitCharacter;
class UBoxComponent;



UCLASS()
class PULSARDEVTEST_API ABaseAI : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAI();
protected:

	virtual void Tick(float DeltaTime) override;

public:
	AUnitCharacter* GetUnitCharacter();
	bool bCanPerformAct;
	void CanPerformAct();

	void AIMove(FVector InLocation);
	virtual void OnPossess(APawn* InPawn) override;

private:

	UBoxComponent* SelectionArea;

	FVector Location;
	FVector Extent;

	FVector CharacterLocation;
	FVector CharacterExtent;

	AUnitCharacter* UnitCharacter;

};
