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




// Called when the game starts or when spawned
void AIslandTile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AIslandTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

