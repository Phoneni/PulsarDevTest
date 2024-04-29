// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPC.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "UnitCharacter.h"
#include "BaseAI.h"
#include <../../../../../Source/Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>
#include <../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include <../../../../../Source/Runtime/Engine/Classes/Components/DecalComponent.h>
#include "NPCInteractive.h"
#include "PulsarWorldSubSystem.h"
#include "../../../../../Source/Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"

ATopDownPC::ATopDownPC()
{
	bShowMouseCursor = true;
	bInMapMode = false;
	DefaultMouseCursor = EMouseCursor::Hand;


	SelectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SelectionArea"));
	SelectionArea->SetBoxExtent(FVector(0));
}

void ATopDownPC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ATopDownPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		check(InputComponent);

		if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			if (CameraMovement)
			{
				PlayerEnhancedInputComponent->BindAction(CameraMovement, ETriggerEvent::Triggered, this, &ATopDownPC::MoveFn);
			}
			if (PawnSelectionPressed)
			{
				PlayerEnhancedInputComponent->BindAction(PawnSelectionPressed, ETriggerEvent::Triggered, this, &ATopDownPC::OnSetDestinationPressed);
			}
			if (PawnSelectionReleased)
			{
				PlayerEnhancedInputComponent->BindAction(PawnSelectionReleased, ETriggerEvent::Triggered, this, &ATopDownPC::OnSetDestinationReleased);
			}
			if (PawnInteraction)
			{
				PlayerEnhancedInputComponent->BindAction(PawnInteraction, ETriggerEvent::Triggered, this, &ATopDownPC::InteractFn);
			}
			if (SetPawnMoveLocation)
			{
				PlayerEnhancedInputComponent->BindAction(SetPawnMoveLocation, ETriggerEvent::Triggered, this, &ATopDownPC::RighClickInput);
			}
			if (OpenMap)
			{
				PlayerEnhancedInputComponent->BindAction(OpenMap, ETriggerEvent::Triggered, this, &ATopDownPC::OpenMapFn);
			}
		}

	}
}

void ATopDownPC::BeginPlay()
{
	Super::BeginPlay();


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, BaseMappingPriority);
	}
}

void ATopDownPC::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	GetHitResultUnderCursor(ECC_Pawn, true, HitResult);
	CalculateMovement(DeltaTime);

	if (LeftMouseDown)
	{
		MousePressTime += DeltaTime;

		MouseEnd = HitResult.Location;

		CenterMouseLoc = FVector((MouseStart + MouseEnd) * 0.5f);
		Dist = FVector::Dist(MouseEnd, MouseStart) * 0.5f;
		SelectionSize = FVector(Dist, Dist, 100);

		if (LeftMouseDown > 0.75f)
		{
			DrawDebugBox(GetWorld(), CenterMouseLoc, SelectionSize, FQuat(0, 0, 0, 0), FColor::Black);
		}
	}
	else
	{
		MousePressTime = 0;
	}
}
void ATopDownPC::CalculateMovement(float DeltaSeconds)
{
	//maybe not needed
}

void ATopDownPC::MoveFn(const FInputActionValue& Value)
{
	if (!bInMapMode)
	{
		const FVector2D MovementValue = Value.Get<FVector2D>();
		FVector MoveForward = GetPawn()->GetActorForwardVector();
		MoveForward.Z = 0.f;
		MoveForward = MoveForward.GetSafeNormal();
		GetPawn()->AddMovementInput(MoveForward, MovementValue.X);

		FVector MoveRight = GetPawn()->GetActorRightVector();
		GetPawn()->AddMovementInput(MoveRight, MovementValue.Y);
	}
}

void ATopDownPC::OpenMapFn()
{
	if (GetWorld())
	{
		UPulsarWorldSubSystem* PWS = GetWorld()->GetSubsystem<UPulsarWorldSubSystem>();
		if (IsValid(PWS))
		{
			if (bInMapMode)
			{
				SetViewTargetWithBlend(GetPawn(), 1.f);
				bInMapMode = false;
				PWS->SetUnitsHidden(false);
				SetMapWidgetVisible(false);
			}
			else if (IsValid(PWS->MapCameraActor))
			{
				SetViewTargetWithBlend(PWS->MapCameraActor, 1.f);
				bInMapMode = true;
				PWS->SetUnitsHidden(true);
				SetMapWidgetVisible(true);
			}
		}
	}
}

void ATopDownPC::SelectUnits()
{
		SelectionArea->SetWorldLocation(CenterMouseLoc);
	SelectionArea->SetBoxExtent(SelectionSize);

	TArray<AActor*>TBSActors;
	SelectionArea->GetOverlappingActors(TBSActors);


	if (TBSActors.Num() > 0)
	{
		SelectedUnits.Empty();

		for (AActor* Temp : TBSActors)
		{
			if (Temp->IsA(AUnitCharacter::StaticClass()))
			{
				AUnitCharacter* ValidCharacter = Cast<AUnitCharacter>(Temp);
				SelectedUnits.Add(Temp);
			}
		}
	}

}


void ATopDownPC::MoveUnits(FVector Loc)
{

	if (SelectedUnits.Num() > 0 && !IsInteracting() && !bInMapMode)
	{
		for (AActor* TempActor : SelectedUnits)
		{
			if (TempActor->IsA(AUnitCharacter::StaticClass()))
			{
				AUnitCharacter* UnitChar = Cast<AUnitCharacter>(TempActor);

				ABaseAI* con = Cast<ABaseAI>(UnitChar->GetController());
				UPathFollowingComponent* PFComp = con->GetPathFollowingComponent();
				if (PFComp && !UnitMoveDelegates.Contains(TempActor))
				{
					FMoveFinishedDelegateData CurrentMoveFinishedDelegateData;
					CurrentMoveFinishedDelegateData.UsedDelegateHandle = PFComp->OnRequestFinished.AddUObject(this, &ATopDownPC::OnUnitMoveFinished);
					con->AIMove(Loc);

					CurrentMoveFinishedDelegateData.UsedRequestID = PFComp->GetCurrentRequestId();
					UnitMoveDelegates.Add(TempActor, CurrentMoveFinishedDelegateData);
				}
			}
		}
		TryRemoveInteractWidget();
	}
}

void ATopDownPC::OnUnitMoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	for (AActor* TempActor : SelectedUnits)
	{
		if (TempActor->IsA(AUnitCharacter::StaticClass()))
		{
			AUnitCharacter* UnitChar = Cast<AUnitCharacter>(TempActor);

			ABaseAI* con = Cast<ABaseAI>(UnitChar->GetController());
			UPathFollowingComponent* PFComp = con->GetPathFollowingComponent();
			if (PFComp)
			{
				FMoveFinishedDelegateData* UsedFinishedData = UnitMoveDelegates.Find(TempActor);
				if (UsedFinishedData && RequestID.GetID() == UsedFinishedData->UsedRequestID)
				{
					ANPCInteractive* InteractableNPC = UnitChar->OverlapForInteractableNPCs();
					if (IsValid(InteractableNPC))
					{
						TrySpawnInteractWidget(InteractableNPC);
					}
					PFComp->OnRequestFinished.Remove(UsedFinishedData->UsedDelegateHandle);
					UnitMoveDelegates.Remove(TempActor);
					break;
				}
			}
		}
	}
}

void ATopDownPC::RighClickInput()
{
	if (HitResult.bBlockingHit)
	{
		MoveUnits(HitResult.Location);
	}


}

void ATopDownPC::MoveToMouseCursor()
{
	if (HitResult.bBlockingHit)
	{
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATopDownPC::SetNewMoveDestination(const FVector Destination)
{
	
	const APawn* TempPawn = GetPawn();
	if (TempPawn)
	{
	
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
	}
}

void ATopDownPC::OnSetDestinationPressed()
{

	LeftMouseDown = true;
	MouseStart = HitResult.Location;
}

void ATopDownPC::OnSetDestinationReleased()
{
	LeftMouseDown = false;
	SelectUnits();
}


