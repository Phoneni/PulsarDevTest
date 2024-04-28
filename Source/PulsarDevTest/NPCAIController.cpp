// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "RoamingNPC.h"
#include "NavigationSystem.h"

ANPCAIController::ANPCAIController()
{
	TravelDist = 1500.f;
	IdleTime = 5.f;
}

void ANPCAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	MoveToRNDLocation();
}

void ANPCAIController::MoveToRNDLocation()
{
	FNavLocation Loc;

	ARoamingNPC* RoamingNPC = Cast<ARoamingNPC>(GetCharacter());

	UNavigationSystemV1::GetCurrent(GetWorld())->GetRandomPointInNavigableRadius(RoamingNPC->GetActorLocation(), TravelDist, Loc);

	MoveToLocation(Loc);

	GetWorld()->GetTimerManager().SetTimer(IdleTimer, this, &ANPCAIController::MoveToRNDLocation, FMath::RandRange(IdleTime - 0.2f, IdleTime + 0.2f));


}
