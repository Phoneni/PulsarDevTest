

#include "TopDownCharacter.h"
#include <../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>

ATopDownCharacter::ATopDownCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CharacterSpringArm"));
	CharacterSpringArm->SetupAttachment(GetRootComponent());
	CharacterSpringArm->SetUsingAbsoluteRotation(true);
	CharacterSpringArm->TargetArmLength = 0.f;
	CharacterSpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CharacterCamera->SetupAttachment(CharacterSpringArm, USpringArmComponent::SocketName);
	CharacterCamera->bUsePawnControlRotation = false;
}

void ATopDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

