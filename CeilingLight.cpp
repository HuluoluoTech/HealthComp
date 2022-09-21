// Fill out your copyright notice in the Description page of Project Settings.


#include "CeilingLight.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACeilingLight::ACeilingLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
    PointLightComp = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComp"));

    //StaticMeshComp->SetupAttachment(RootComponent);

    PointLightComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    PointLightComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    PointLightComp->SetWorldLocation(FVector(0, 0, -130));

    Brightness = 1700.f;
    Color = FLinearColor(1.f, 0.77f, 0.46f);
    SourceRadius = 3.5f;

    PointLightComp->SetIntensity(Brightness);
    PointLightComp->SetLightColor(Color);
    PointLightComp->SetSourceRadius(SourceRadius);

  /*  BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    BoxComp->SetBoxExtent(FVector(128, 128, 64));
    BoxComp->SetVisibility(true);
    BoxComp->SetHiddenInGame(false);*/

}

// Called when the game starts or when spawned
void ACeilingLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACeilingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACeilingLight::OnInteract()
{
    ToggleLight();
}

void ACeilingLight::ToggleLight()
{
    if (bIsLightOn)
    {
        PointLightComp->SetVisibility(false);
        bIsLightOn = false;
    }
    else
    {
        PointLightComp->SetVisibility(true);
        bIsLightOn = true;
    }

   /* bIsLightOn = !bIsLightOn;
    PointLightComp->SetVisibility(bIsLightOn);*/
}

