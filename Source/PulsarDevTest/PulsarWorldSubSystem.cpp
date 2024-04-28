// Fill out your copyright notice in the Description page of Project Settings.


#include "PulsarWorldSubSystem.h"

void UPulsarWorldSubSystem::RegisterUnit(AActor* InUnit)
{
	Units.Add(InUnit);
}

void UPulsarWorldSubSystem::UnregisterUnit(AActor* InUnit)
{
	Units.Remove(InUnit);
}

void UPulsarWorldSubSystem::RegisterMapCameraActor(AActor* InCameraActor)
{
	MapCameraActor = InCameraActor;
}

void UPulsarWorldSubSystem::SetUnitsHidden(bool bHidden)
{
	for (int32 i = Units.Num() - 1; i >= 0; i--)
	{
		AActor*& ObservedUnit = Units[i];
		if (IsValid(ObservedUnit))
		{
			ObservedUnit->SetActorHiddenInGame(bHidden);
		}
		else
		{
			Units.RemoveAt(i);
		}
	}
}
