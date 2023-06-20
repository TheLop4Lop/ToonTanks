// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCnt();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);

        FTimerHandle PlayerEnableTimerHandle;

        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, TimerDelegate, StartDelay, false);
    }

}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();

        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);
        }

        GameOver(false);
    
    //Try to cast a ATower about to being destroyed, if succesfull destroy the Tower
    }else if(ATower* DestoyerTower = Cast<ATower>(DeadActor))
    {
        DestoyerTower->HandleDestruction();
        --TargetTowers;

        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }

}

int32 AToonTanksGameMode::GetTargetTowerCnt()
{
    TArray<AActor*> TowersInWorld;

    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowersInWorld);

    return TowersInWorld.Num();

}

int32 AToonTanksGameMode::GetTowers()
{
    return TargetTowers;
}