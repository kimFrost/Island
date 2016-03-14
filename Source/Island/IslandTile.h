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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	FVector PeopleLocationDisplacement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool TileExplored;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool TileHidden;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	bool TileCanBeBypassed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	FST_Card TileCard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	TArray<FString> CardsAllowed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	UStaticMeshComponent* BaseMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	//UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UMaterialInstanceDynamic* DynamicMaterial;

	// Dynamic material for param


	/*********** FUNCTIONS **************/

	UFUNCTION(BlueprintCallable, Category = "Person")
	FVector PlacePerson(AIslandPerson* Person, bool Teleport);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void RemovePerson(AIslandPerson* Person);

	UFUNCTION(BlueprintCallable, Category = "Person")
	void UpdatePersonPlacements();

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void CheckTile();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TileClicked();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TileHoverBegin();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TileHoverEnd();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnAnyTileSelected(AIslandTile* Tile);

public:

	/*********** OVERRIDES **************/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// OnConstruction
	//virtual void OnConstruction(const FTransform& Transform) override;


};
