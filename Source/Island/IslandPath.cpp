// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandTile.h"
#include "IslandPath.h"


// Sets default values
AIslandPath::AIslandPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileA = nullptr;
	TileB = nullptr;
	NumOfIntersections = 0;
	bOneWay = false;
}

// Called when the game starts or when spawned
void AIslandPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIslandPath::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void AIslandPath::PreEditChange(UProperty* PropertyThatWillChange)
{
	Super::PreEditChange(PropertyThatWillChange);
	
	//PropertyThatWillChange
	
	//~~ Remove Path reference from tiles in reference. Will be added in OnConstruction or PostEditChangeProperty again ~~~//
	if (TileA)
	{
		TileA->Paths.Remove(this);
	}
	if (TileB)
	{
		TileB->Paths.Remove(this);
	}
}


void AIslandPath::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	//e.Property
	if (TileA)
	{
		TileA->Paths.Add(this);
	}
	if (TileB)
	{
		TileB->Paths.Add(this);
	}
}


void AIslandPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UE_LOG(LogTemp, Warning, TEXT("Path::OnConstruction"));



}