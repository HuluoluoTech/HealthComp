// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RespawnPlayerGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

/**
 * 
 */
UCLASS(minimalapi)
class ARespawnPlayerGameMode : public AGameModeBase
{
    GENERATED_BODY()

    ARespawnPlayerGameMode();
	
public:
    const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

    //Tries to Spawn the player's pawn.
    // RestartPlayer is a method that already exists within the GameModeBase class. It tries to spawn the player's Pawn at the location returned by FindPlayerStart.
    virtual void RestartPlayer(AController* NewPlayer) override;

protected:
    virtual void BeginPlay() override;

    //Called when Player character has died.
    UFUNCTION()
        virtual void PlayerDied(ACharacter* Character);

    //Signature to bind delegate. 
    UPROPERTY()
        FOnPlayerDiedSignature OnPlayerDied;
};
