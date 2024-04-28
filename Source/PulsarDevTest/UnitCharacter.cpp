

#include "UnitCharacter.h"
#include "TopDownPC.h"
#include "NPCInteractive.h"
#include "PulsarWorldSubSystem.h"

AUnitCharacter::AUnitCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUnitCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		UPulsarWorldSubSystem* PWS = GetWorld()->GetSubsystem<UPulsarWorldSubSystem>();
		if (IsValid(PWS))
		{
			PWS->RegisterUnit(this);
		}
	}
}

void AUnitCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		UPulsarWorldSubSystem* PWS = GetWorld()->GetSubsystem<UPulsarWorldSubSystem>();
		if (IsValid(PWS))
		{
			PWS->UnregisterUnit(this);
		}
	}
}

void AUnitCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ANPCInteractive* AUnitCharacter::OverlapForInteractableNPCs()
{
	TArray<FOverlapResult> TempArr;
	FCollisionObjectQueryParams ObjectQP;
	FCollisionQueryParams QueryParams;

	ObjectQP.AddObjectTypesToQuery(ECC_Pawn);
	QueryParams.AddIgnoredActor(this);

	const bool bOverlapResulst = GetWorld()->OverlapMultiByObjectType(TempArr, GetActorLocation(), GetActorRotation().Quaternion(),
		ObjectQP, FCollisionShape::MakeSphere(300), QueryParams);

	if (bOverlapResulst)
	{
		for (const FOverlapResult& Temp : TempArr)
		{
			ANPCInteractive* PotentialInteractable = Cast<ANPCInteractive>(Temp.GetActor());

			if (IsValid(PotentialInteractable))
			{
				return PotentialInteractable;
			}
		}
	}
	return nullptr;
}

