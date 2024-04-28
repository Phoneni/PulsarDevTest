
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UnitCharacter.generated.h"

class ANPCInteractive;

UCLASS()
class PULSARDEVTEST_API AUnitCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUnitCharacter();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	ANPCInteractive* OverlapForInteractableNPCs();

};
