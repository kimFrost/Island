// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandPerson.h"
#include "IslandTile.generated.h"


UCLASS()
class ISLAND_API AIslandTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandTile(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool IsCamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<AIslandTile*> PathTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<AIslandTile*> HiddenPathTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<AIslandPerson*> PeopleOnTile;

	// Cards that fit

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
