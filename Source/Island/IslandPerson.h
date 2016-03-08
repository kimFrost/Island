// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandDataHolder.h"
#include "IslandPerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;


UCLASS()
class ISLAND_API AIslandPerson : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandPerson(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FST_Person PersonRawData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	int32 ActionsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	AIslandTile* TilePlacedOn;

	//~~ FUNCTIONS ~~//

	UFUNCTION(BlueprintCallable, Category = "Input")
	void PersonClicked();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
