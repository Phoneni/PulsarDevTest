// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAI.generated.h"


class AUnitCharacter;
class UBoxComponent;

UENUM(BlueprintType)
enum class EActionType : uint8 
{
	Move,
	Talk,
	MapOpen,
	End
};

UCLASS()
class PULSARDEVTEST_API ABaseAI : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseAI();
protected:

	virtual void Tick(float DeltaTime) override;

public:
	void TalkAction();
	AUnitCharacter* GetUnitCharacter();
	void SetTargetActor(AActor* InActor);
	AActor* GetTargetActor() const { return TargetActor; }

	bool bCanPerformAct;
	void CanPerformAct();

	void AIMove(FVector InLocation);
	virtual void OnPossess(APawn* InPawn) override;

private:
	AActor* PrevTarget;
	AActor* TargetActor;
	UBoxComponent* SelectionArea;

	FVector Location;
	FVector Extent;

	FVector CharacterLocation;
	FVector CharacterExtent;

	AUnitCharacter* UnitCharacter;
	EActionType CurrAction;

};
