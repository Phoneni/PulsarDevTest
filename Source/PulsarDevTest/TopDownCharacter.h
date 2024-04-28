// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PULSARDEVTEST_API ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownCharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPirvateAccess = "true"))
	UCameraComponent* CharacterCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPirvateAccess = "true"))
	USpringArmComponent* CharacterSpringArm;
};
