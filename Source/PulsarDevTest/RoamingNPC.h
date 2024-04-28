#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoamingNPC.generated.h"


UCLASS()
class PULSARDEVTEST_API ARoamingNPC : public ACharacter
{
	GENERATED_BODY()

public:
	ARoamingNPC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
