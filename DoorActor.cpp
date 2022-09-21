// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //Create our Default Components
    DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));

    //Setup our Attachments
    DoorFrame->SetupAttachment(RootComponent);

    // Ìí¼Óµ½ Component 
    Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
    Door->SetRelativeLocation(FVector(0, 35, 0));
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

    //Binding our float track to our UpdateTimelineComp Function's output
    UpdateFunctionFloat.BindDynamic(this, &ADoorActor::UpdateTimelineComp);

    //If we have a float curve, bind it's graph to our update function
    if (DoorTimelineFloatCurve)
    {
        UE_LOG(LogTemp, Warning, TEXT("AddInterpFloat"));

        // Add a float interpolation (²åÖµ) to the timeline
        DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
    }

    if (BossActorReference)
    {
        UE_LOG(LogTemp, Warning, TEXT("BossActorReference"));

        BossActorReference->OnBossDied.BindUObject(this, &ADoorActor::BossDiedEventFunction);
    }
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorActor::BossDiedEventFunction()
{
    UE_LOG(LogTemp, Warning, TEXT("BossDiedEventFunction"));

    // Start playback of timeline
    DoorTimelineComp->Play();
}

void ADoorActor::UpdateTimelineComp(float Output)
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateTimelineComp %f"), Output);

    // Create and set our Door's new relative location based on the output from our Timeline Curve
    FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
    Door->SetRelativeRotation(DoorNewRotation);
}

