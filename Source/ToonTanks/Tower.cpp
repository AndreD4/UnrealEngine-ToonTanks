// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Find the distance to the tank
    if(Tank)
    {
      float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    
    
    // Check to see if the tank is in range
    if(Distance <= FireRange)
    {
      // If tank is in Range, rotate tower facing tank
      RotateTurret(Tank->GetActorLocation());
    }
  } 
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if(Distance <= FireRange)
        {
          Fire();
        }
    }
}