// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandDataHolder.h"
#include "IslandPerson.h"


// Sets default values
AIslandPerson::AIslandPerson(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActionsLeft = 0;
	OnClicked.AddDynamic(this, &AIslandPerson::PersonClicked);

	TilePlacedOn = nullptr;

	//static_cast<UStaticMeshComponent*>(GlobeComponent)->OnClicked.AddDynamic(this, &AWorldPawn::DoMeshOnClicked);
}


void AIslandPerson::PersonClicked() {
	//UE_LOG(LogTemp, Log, TEXT("pawn clicked"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandPerson:PersonClicked");


}

/*
void AIslandPerson::DoMeshOnClicked(UPrimitiveComponent* clicked) {
	UE_LOG(LogTemp, Log, TEXT("mesh clicked"));
}
*/

// Called when the game starts or when spawned
void AIslandPerson::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIslandPerson::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

