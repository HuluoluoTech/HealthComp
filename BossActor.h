// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"

DECLARE_DELEGATE(FOnBossDiedDelegate);

UCLASS()
class HEALTHCOMP_API ABossActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION()
		void HandleBossDiedEvent();
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class UBoxComponent* BoxComp;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:
	FOnBossDiedDelegate OnBossDied;
};
