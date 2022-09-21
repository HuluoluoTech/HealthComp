// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"

#include "CeilingLight.generated.h"

UCLASS()
class HEALTHCOMP_API ACeilingLight : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void OnInteract();
	
public:	
	// Sets default values for this actor's properties
	ACeilingLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UPointLightComponent* PointLightComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Brightness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float SourceRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool bIsLightOn;

    UFUNCTION()
        void ToggleLight();

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
    class UBoxComponent* BoxComp;

};
