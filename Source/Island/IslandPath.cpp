// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandPath.h"


// Sets default values
AIslandPath::AIslandPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

