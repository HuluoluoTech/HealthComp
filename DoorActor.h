// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "BossActor.h"
#include "DoorActor.generated.h"

// TimelineComponent holds a series of events, floats, vectors or colors with associated keyframes.

UCLASS()
class HEALTHCOMP_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Variable to hold the Curve asset
	UPROPERTY(EditAnywhere)
		UCurveFloat* DoorTimelineFloatCurve;

protected:
    void BossDiedEventFunction();
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
        class ABossActor* BossActorReference;

    //MeshComponents to represent Door assets
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* DoorFrame;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* Door;

    //TimelineComponent to animate Door meshes
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        UTimelineComponent* DoorTimelineComp;

    //Float Track Signature to handle our update track event
    FOnTimelineFloat UpdateFunctionFloat;

    //Function which updates our Door's relative location with the timeline graph
    UFUNCTION()
        void UpdateTimelineComp(float Output);
};
