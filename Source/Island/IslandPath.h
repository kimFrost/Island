// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandPath.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;



UCLASS()
class ISLAND_API AIslandPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandPath();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// PathLink

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	AIslandTile* TileA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	AIslandTile* TileB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	int32 NumOfIntersections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	bool bOneWay;

	// Destinations

	// Tile A

	// Tile B

	// bOneWay // A -> B


	// Update on construction script?

	virtual void PreEditChange(UProperty* PropertyThatWillChange) override;
	
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void OnConstruction(const FTransform& Transform) override;


};
