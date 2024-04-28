#include "BaseAI.h"
#include <../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h>
#include "UnitCharacter.h"
#include "TopDownPC.h"


ABaseAI::ABaseAI() : Super()
{
	bCanPerformAct = true;
	SelectionArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SelectionArea"));
	SelectionArea->SetBoxExtent(FVector(1500, 1500, 1500));
}

void ABaseAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAI::TalkAction()
{
	//TODO
}

AUnitCharacter* ABaseAI::GetUnitCharacter()
{
	if (UnitCharacter == nullptr)
	{
		UnitCharacter = Cast<AUnitCharacter>(GetCharacter());
	}
	return UnitCharacter;
}

void ABaseAI::SetTargetActor(AActor* InActor)
{
	PrevTarget = TargetActor;
	TargetActor = InActor;
}

void ABaseAI::CanPerformAct()
{
	bCanPerformAct = true;
}

void ABaseAI::AIMove(FVector InLocation)
{

	TargetActor = nullptr;
	MoveToLocation(InLocation, 150.f);
	CurrAction = EActionType::Move;
}

void ABaseAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//TODO
}
