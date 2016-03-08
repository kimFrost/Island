// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "Kismet/GameplayStatics.h"
#include "IslandGameInstance.h"
#include "IslandPlayerController.h"
#include "IslandTile.h"


// Sets default values
AIslandTile::AIslandTile(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsCamp = false;

	OnClicked.AddDynamic(this, &AIslandTile::TileClicked);
	//OnReleased
	OnBeginCursorOver.AddDynamic(this, &AIslandTile::TileHoverBegin);
	OnEndCursorOver.AddDynamic(this, &AIslandTile::TileHoverEnd);

	PeopleLocationDisplacement = FVector(100, 100, 0);

	TileExplored = false;
	TileHidden = false;
	TileCanBeBypassed = false;

	// OnClicked.AddDynamic(this, &AWorldPawn::DoOnClicked);


	//col = PCIP.CreateDefaultSubobject(this, TEXT("light")); col->OnClicked.AddDynamic(this, &AMyActor::OnClick);
	//exitButton->OnClicked.AddDynamic(this, &URoMMainMenuWidget::exitGame);

	/*
	 ShipMesh->OnClicked.AddDynamic(this, &AShipActor::OnClicked);

	void AShipActor::OnClicked(UPrimitiveComponent* pComponent){
		//my logic
	}
	
	*/
}


/******************** PlacePerson *************************/
int32 AIslandTile::PlacePerson(AIslandPerson* Person)
{
	int32 Index;
	//~~ From from previous tile ~~//
	if (Person->TilePlacedOn)
	{
		Person->TilePlacedOn->RemovePerson(Person);
	}
	//~~ Add to new tile ~~//
	Index = PeopleOnTile.Add(Person);
	FVector NewLocation = this->GetActorLocation() + (FVector(50, 0, 0) * Index) + PeopleLocationDisplacement;
	Person->SetActorLocation(NewLocation);
	Person->TilePlacedOn = this;

	

	return Index;
}


/******************** CheckTile *************************/
void AIslandTile::CheckTile()
{
	if (!TileExplored)
	{
		// Trigger tile event reveal
		//TileCard
		UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->OnTileRevealed.Broadcast(this);
		}
	}
}


/******************** RemovePerson *************************/
void AIslandTile::RemovePerson(AIslandPerson* Person)
{
	PeopleOnTile.Remove(Person);
	UpdatePersonPlacements();
}


/******************** UpdatePersonPlacements *************************/
void AIslandTile::UpdatePersonPlacements()
{
	for (int32 i = 0; i < PeopleOnTile.Num(); i++)
	{
		AIslandPerson* Person = PeopleOnTile[i];
		FVector NewLocation = this->GetActorLocation() + (FVector(50, 0, 0) * i) + PeopleLocationDisplacement;
		Person->SetActorLocation(NewLocation);
	}
}


/******************** TileClicked *************************/
void AIslandTile::TileClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "IslandTile::TileClicked");
	//UIslandGameInstance GameInstance = Cast<UIslandGameInstance>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AIslandPlayerController* PlayerController = Cast<AIslandPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->CenterCameraAt(GetActorLocation());
	}
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnTileSelected.Broadcast(this);
	}
}


/******************** TileHoverBegin *************************/
void AIslandTile::TileHoverBegin()
{

}


/******************** TileHoverEnd *************************/
void AIslandTile::TileHoverEnd()
{

}

/******************** Test *************************/
void AIslandTile::Test(AIslandTile* Tile)
{

}


// Called when the game starts or when spawned
void AIslandTile::BeginPlay()
{
	Super::BeginPlay();

	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnTileSelected.AddDynamic(this, &AIslandTile::Test);
	}


}

// Called every frame
void AIslandTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

