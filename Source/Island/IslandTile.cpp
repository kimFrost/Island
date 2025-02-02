// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "Kismet/GameplayStatics.h"
#include "IslandGameInstance.h"
#include "IslandPath.h"
#include "IslandPlayerController.h"
#include "IslandTile.h"


// Sets default values
AIslandTile::AIslandTile(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsCamp = false;
	DistanceFromSelectedPerson = 0;

	OnClicked.AddDynamic(this, &AIslandTile::TileClicked);
	//OnReleased
	OnBeginCursorOver.AddDynamic(this, &AIslandTile::TileHoverBegin);
	OnEndCursorOver.AddDynamic(this, &AIslandTile::TileHoverEnd);

	PeopleLocationDisplacement = FVector(300, 300, 50);

	bTileExplored = false;
	bTileHidden = true;
	TileCanBeBypassed = false;

	Selected = false;

	PathTo = TArray<AIslandTile*>();

	USceneComponent* const TranslationComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	TranslationComp->Mobility = EComponentMobility::Static;
	RootComponent = TranslationComp;

	// OnClicked.AddDynamic(this, &AWorldPawn::DoOnClicked);

	//col = PCIP.CreateDefaultSubobject(this, TEXT("light")); col->OnClicked.AddDynamic(this, &AMyActor::OnClick);
	//exitButton->OnClicked.AddDynamic(this, &URoMMainMenuWidget::exitGame);

	/*
	 ShipMesh->OnClicked.AddDynamic(this, &AShipActor::OnClicked);

	void AShipActor::OnClicked(UPrimitiveComponent* pComponent){
		//my logic
	}
	
	*/

	// Basemesh ~~//

	//StaticMesh'/Game/Meshes/Tile/tile.tile'

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BaseMeshObj(TEXT("StaticMesh'/Game/Meshes/Tile/tile.tile'"));
	if (BaseMeshObj.Succeeded())
	{
		BaseMesh->SetStaticMesh(BaseMeshObj.Object);
	}
	BaseMesh->AttachParent = RootComponent;

	

	//static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialInstanceObj(TEXT("MaterialInstanceConstant'/Game/Materials/Selected/M_SelectedTest_Inst.M_SelectedTest_Inst'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialInstanceObj(TEXT("MaterialInstanceConstant'/Game/Meshes/Tile/M_TileEdgeLine_Inst.M_TileEdgeLine_Inst'"));
	if (BaseMesh && MaterialInstanceObj.Succeeded())
	{
		//Material = MaterialInstanceObj.Object;
		//BaseMesh->SetMaterial(0, Material);
		//BaseMesh->SetMaterial(0, MaterialInstanceObj.Object);
		//DynamicMaterial = (UMaterialInstanceDynamic*)MaterialInstanceObj.Object;
		//DynamicMaterial = BaseMesh->CreateDynamicMaterialInstance(0);
		//DynamicMaterial->SetScalarParameterValue("ParamWhatever", 1.f);

		//DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialInstanceObj.Object, this);

		//BaseMesh->SetMaterial(0, DynamicMaterial);
		//DynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::White);

		//BaseMesh->SetMaterial(0, MaterialInstanceObj.Object);
		
		//DynamicMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
		//DynamicMaterial = BaseMesh->CreateDynamicMaterialInstance(0);
		//DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::White);


		//BaseMesh->SetMaterial(1, MaterialInstanceObj.Object);
		//DynamicMaterial = BaseMesh->CreateDynamicMaterialInstance(1);
		//DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::Gray);
	}



	//~~ Indicator ~~//
	MoveToIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MoveToIndicatorMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MoveToIndicatorMeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (MoveToIndicatorMeshObj.Succeeded())
	{
		MoveToIndicatorMesh->SetStaticMesh(MoveToIndicatorMeshObj.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>MoveToIndicatorMaterialObj(TEXT("Material'/Game/Materials/Indicator/M_Indicator.M_Indicator'"));
	if (MoveToIndicatorMaterialObj.Succeeded())
	{
		MoveToIndicatorMesh->SetMaterial(0, MoveToIndicatorMaterialObj.Object);
	}

	MoveToIndicatorMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	MoveToIndicatorMesh->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
	MoveToIndicatorMesh->RelativeLocation = FVector(0, 0, 260);
	MoveToIndicatorMesh->AttachParent = RootComponent;
	MoveToIndicatorMesh->SetVisibility(false);
	MoveToIndicatorMesh->SetCastShadow(false);




	

	/*
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialInstanceObj(TEXT("MaterialInstanceConstant'/Game/Materials/Decals/M_HexDecal_Inst.M_HexDecal_Inst'"));
	if (MaterialInstanceObj.Succeeded())
	{
		Material = MaterialInstanceObj.Object;
		GetDecal()->SetMaterial(0, Material);
		DynamicMaterial = GetDecal()->CreateDynamicMaterialInstance();
		SetMaterial(0, DynamicMaterial);
		//DynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Yellow);
	}
	*/
	//DynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);


	//MatInst = ((UPrimitiveComponent*)GetRootComponent())->CreateAndSetMaterialInstanceDynamic(0);

	/*
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/UI/Game/M_Reload.M_Reload'"));
	if (Material.Object)
	{
		ReloadDisplay->AddElement((UMaterialInterface*)Material.Object, nullptr, false, 32.0f, 32.0f, nullptr);
	}
	*/

	
}


/******************** PlacePerson *************************/
FVector AIslandTile::PlacePerson(AIslandPerson* Person, bool Teleport, bool StoreInTile)
{
	int32 Index;
	FVector NewLocation;
	if (Person)
	{
		//~~ From from previous tile ~~//
		if (Person->TilePlacedOn)
		{
			Person->TilePlacedOn->RemovePerson(Person);
		}
		//~~ Add to new tile ~~//
		if (StoreInTile)
		{
			Index = PeopleOnTile.Add(Person);
			NewLocation = this->GetActorLocation() + (FVector(0, 500, 0) * Index) + PeopleLocationDisplacement;
			if (Teleport)
			{
				Person->SetActorLocation(NewLocation);
			}
			Person->TilePlacedOn = this;

		}
		// Get all steps/tiles pathto?
	}
	//return Index;
	return NewLocation;
}


/******************** ShowTile *************************/
void AIslandTile::ShowTile()
{
	if (bTileHidden)
	{
		RootComponent->SetVisibility(true, true);
		bTileHidden = false;

		OnTileRevealed.Broadcast(this);

		UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->OnTileRevealed.Broadcast(this);
		}

		//Paths.Num() // remove trees along path
	}
}


/******************** HideTile *************************/
void AIslandTile::HideTile()
{
	if (!bTileHidden)
	{
		RootComponent->SetVisibility(false, true);
		bTileHidden = true;
	}
}



/******************** OnTileRevealed *************************/
/*
void AIslandTile::OnTileRevealed_Implementation()
{
	// No logic here. Used for blueprint event binding
}
*/


/******************** CheckTile *************************/
void AIslandTile::CheckTile()
{
	if (!bTileExplored)
	{
		bTileExplored = true;
		ShowTile();

		for (int32 i = 0; i < Paths.Num(); i++)
		{
			AIslandPath* Path = Paths[i];
			if (Path)
			{
				Path->SetPathVisibility_Implementation(true);
				//Path->SetPathVisibility(true); //!! Won't work apparently
			}
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
		if (Person)
		{
			FVector NewLocation = this->GetActorLocation() + (FVector(50, 0, 0) * i) + PeopleLocationDisplacement;
			Person->SetActorLocation(NewLocation);
		}
	}
}


/******************** GetTileAvailableActions *************************/
TArray<FST_Action> AIslandTile::GetTileAvailableActions(AIslandPerson* Person)
{
	TArray<FST_Action> Actions;
	for (auto& Action : TileCard.Actions)
	{
		
	}

	Actions = TileCard.Actions;

	//?? Hidden path search? ??//


	// TileCard.Conditions

	// TileCard.NotConditions


	//CompletedEvents


	//~~ Parse string parameters $name etc. ~~//
	for (auto& Action : Actions)
	{
		for (auto& Event : Action.Events)
		{
			
		}
		//Action.Title.Replace();
	}

	return Actions;
}

/******************** PerformTileAction *************************/
void AIslandTile::PerformTileAction(AIslandPerson* ByPerson, FST_Action Action)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandTile:PerformTileAction");



	for (auto& Event : Action.Events)
	{
		//~~ Pick and find event in event datatable ~~//

		//~~ Parse string parameters $name etc. ~~//
	}

	/*
	switch (Action)
	{
		case ETileActions::DoNothing:
		{
			break;
		}
		case ETileActions::Explore:
		{
			// Items
			// Artifacts
			// Events
			// Hidden paths

			break;
		}
	}
	*/
}


/******************** SelectTile *************************/
void AIslandTile::SelectTile()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::Yellow);
		Selected = true;
		MoveToIndicatorMesh->SetVisibility(true);
	}
}


/******************** DeselectTile *************************/
void AIslandTile::DeselectTile()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue("Color", FLinearColor::Black);
		Selected = false;
		MoveToIndicatorMesh->SetVisibility(false);
	}
}


/******************** TileClicked *************************/
void AIslandTile::TileClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "IslandTile::TileClicked");
	//UIslandGameInstance GameInstance = Cast<UIslandGameInstance>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		/*
		//~~ Select first person ~~//
		if (PeopleOnTile.Num() > 0)
		{
			GameInstance->OnPersonSelected.Broadcast(PeopleOnTile[0]);
			PeopleOnTile[0]->SelectPerson();
		}
		//~~ Else select nullptr ~~//
		else
		{
			GameInstance->OnPersonSelected.Broadcast(nullptr);
		}
		*/
		AIslandPlayerController* PlayerController = Cast<AIslandPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			//PlayerController->CenterCameraAt(GetActorLocation());
		}
		GameInstance->OnTileClicked.Broadcast(this);
		SelectTile();
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

/******************** OnAnyTileClicked *************************/
void AIslandTile::OnAnyTileClicked(AIslandTile* Tile)
{
	if (Tile != this)
	{
		DeselectTile();
	}
}


// Called when the game starts or when spawned
void AIslandTile::BeginPlay()
{
	Super::BeginPlay();
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnTileClicked.AddDynamic(this, &AIslandTile::OnAnyTileClicked);
		TileCard = GameInstance->GetRandCard(EIslandCardType::Tile);
	}
	//~~ Make the tile default hidden ~~//
	if (bTileHidden)
	{
		HideTile();
	}
	//~~ If any people placed on tile ~~//
	if (PeopleOnTile.Num() > 0)
	{
		CheckTile();
	}
}

// Called every frame
void AIslandTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AIslandTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UE_LOG(LogTemp, Warning, TEXT("Tile::OnConstruction"));


}