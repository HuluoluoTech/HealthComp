// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnPlayerGameMode.h"
#include "HealthCompCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARespawnPlayerGameMode::ARespawnPlayerGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

void ARespawnPlayerGameMode::BeginPlay()
{
    Super::BeginPlay();

    //Bind our Player died delegate to the Gamemode's PlayerDied function.
    if (!OnPlayerDied.IsBound())
    {
        OnPlayerDied.AddDynamic(this, &ARespawnPlayerGameMode::PlayerDied);
    }
}

void ARespawnPlayerGameMode::RestartPlayer(AController* NewPlayer)
{
    Super::RestartPlayer(NewPlayer);
}

void ARespawnPlayerGameMode::PlayerDied(ACharacter* Character)
{
    //Get a reference to our Character's Player Controller
    AController* CharacterController = Character->GetController();
    RestartPlayer(CharacterController);
}