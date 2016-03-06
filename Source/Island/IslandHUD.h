// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "IslandTile.h"
#include "IslandHUD.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND_API AIslandHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AIslandHUD(const FObjectInitializer &ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<AIslandTile*> Tiles;


	/****** FUNCTIONS ******/



	/****** OVERRIDES ******/

	//~~ BeginPlay ~~//
	virtual void BeginPlay() override;

	//~~ Tock ~~//
	virtual void Tick(float DeltaSeconds) override;

};
