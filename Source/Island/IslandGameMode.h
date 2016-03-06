// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "IslandGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND_API AIslandGameMode : public AGameMode
{
	GENERATED_BODY()


public:
	AIslandGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	
	
};
