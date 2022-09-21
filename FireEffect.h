// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FireEffect.generated.h"

UCLASS()
class HEALTHCOMP_API AFireEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	//Get the fire sound effect Audio Component.
	UAudioComponent* GetFireAudioComponent() const { return FireAudio; }

	//Get the fire effects Particle System Component.
	UParticleSystemComponent* GetParticleFireComponent() const { return ParticleFire; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UParticleSystemComponent* ParticleFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UAudioComponent* FireAudio;

};
