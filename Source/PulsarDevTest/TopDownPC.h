// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <InputActionValue.h>
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "TopDownPC.generated.h"

class UInputMappingContext;
class UInputAction;
class UNiagaraSystem;
class AUnitCharacter;
class UBoxComponent;
class ATopDownCharacter;

struct FMoveFinishedDelegateData
{
public:
	FDelegateHandle UsedDelegateHandle;
	uint32 UsedRequestID;
};

UCLASS()
class PULSARDEVTEST_API ATopDownPC : public APlayerController
{
	GENERATED_BODY()

public:

	ATopDownPC();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float PressThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* CursorFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Mappings")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Mappings")
	int32 BaseMappingPriority;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
	UInputAction* CameraMovement;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
	UInputAction* PawnSelectionPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
	UInputAction* PawnSelectionReleased;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
	UInputAction* PawnInteraction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
	UInputAction* SetPawnMoveLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Controls|Input Actions")
	UInputAction* OpenMap;

private:
	TMap<AActor*, FMoveFinishedDelegateData> UnitMoveDelegates;
	bool bInMapMode;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void TrySpawnInteractWidget(ANPCInteractive* InteractedActor);
	UFUNCTION(BlueprintImplementableEvent)
	void TryRemoveInteractWidget();
	UFUNCTION(BlueprintImplementableEvent)
	void SetMapWidgetVisible(bool bVisible);

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay();
	virtual void PlayerTick(float DeltaTime) override;
	void CalculateMovement(float DeltaSeconds);
	void MoveFn(const FInputActionValue& Value);
	UFUNCTION(BlueprintImplementableEvent)
	void InteractFn();
	void OpenMapFn();
		
	void SelectUnits();
	void MoveUnits(FVector Loc);
	void RighClickInput();
	void MoveToMouseCursor();

	void SetNewMoveDestination(const FVector Destination);
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	UFUNCTION(BlueprintImplementableEvent)
	bool IsInteracting();

private:
	void OnUnitMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);

private:
	FVector DesiredDestination;	
	TArray<AActor*> SelectedUnits;
	UBoxComponent* SelectionArea;
	ATopDownCharacter* PlayerCharacter;

	FVector MouseStart;
	FVector MouseEnd;
	FVector CenterMouseLoc;
	FVector SelectionSize;
	FHitResult HitResult;

	float MousePressTime;
	float Dist;
	uint32 LeftMouseDown : 1;

	
};
