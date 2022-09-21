// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(128, 128, 64));
	BoxComp->SetVisibility(true);
	BoxComp->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABossActor::HandleBossDiedEvent()
{
	OnBossDied.ExecuteIfBound();
}

// both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events
void ABossActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ABossActor::NotifyActorBeginOverlap"));

	HandleBossDiedEvent();
}
