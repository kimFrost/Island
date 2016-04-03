// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.h"
#include "IslandPlayerController.h"
#include "IslandTile.h"
#include "IslandPath.h"
#include "IslandPerson.h"


// Sets default values
AIslandPerson::AIslandPerson(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovePointsLeft = 2;
	PersonState = EIslandPersonState::Idle;
	Selected = false;

	bEatenThisTurn = true;
	TurnsStaving = 0;

	OnClicked.AddDynamic(this, &AIslandPerson::PersonClicked);

	TilePlacedOn = nullptr;
	TestTileRef = nullptr;
	//MoveCurve = nullptr;

	//static_cast<UStaticMeshComponent*>(GlobeComponent)->OnClicked.AddDynamic(this, &AWorldPawn::DoMeshOnClicked);

	//StaticMesh'/Game/Meshes/SM_TestPerson.SM_TestPerson'
	//StaticMesh'/Game/Meshes/Cylinder_Brush_StaticMesh.Cylinder_Brush_StaticMesh'

	USceneComponent* const TranslationComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	TranslationComp->Mobility = EComponentMobility::Movable;
	RootComponent = TranslationComp;


	//~~ Person Mesh ~~//
	PersonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PersonMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>PersonMeshObj(TEXT("StaticMesh'/Game/Meshes/SM_TestPerson.SM_TestPerson'"));
	if (PersonMeshObj.Succeeded())
	{
		PersonMesh->SetStaticMesh(PersonMeshObj.Object);
		PersonMesh->RelativeLocation = FVector(0, 70, 260);
		PersonMesh->Mobility = EComponentMobility::Movable;
		PersonMesh->AttachParent = RootComponent;
	}



	


	//~~ Person Material ~~//
	/*
	static ConstructorHelpers::FObjectFinder<UMaterial>MaterialObj(TEXT("Material'/Game/Materials/Selected/M_SelectedTest.M_SelectedTest'"));
	if (MaterialObj.Succeeded())
	{
		PersonMeshMaterial = MaterialObj.Object;
	}
	*/

	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialInstanceObj(TEXT("MaterialInstanceConstant'/Game/Materials/Selected/M_SelectedTest_Inst.M_SelectedTest_Inst'"));
	if (MaterialInstanceObj.Succeeded())
	{
		PersonMeshMaterial = MaterialInstanceObj.Object;
	}

	/*
	//~~ Person Material ~~//
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialInstanceObj(TEXT("MaterialInstanceConstant'/Game/Materials/Selected/M_SelectedTest_Inst.M_SelectedTest_Inst'"));
	if (PersonMesh && MaterialInstanceObj.Succeeded())
	{
		PersonMesh->SetMaterial(0, MaterialInstanceObj.Object);
		//PersonMeshDynamicMaterial = PersonMesh->CreateDynamicMaterialInstance(0, PersonMesh->GetMaterial(0));
		//PersonMeshDynamicMaterial = PersonMesh->CreateDynamicMaterialInstance(0, MaterialInstanceObj.Object);
		//PersonMeshDynamicMaterial = PersonMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MaterialInstanceObj.Object);
		//PersonMeshDynamicMaterial = PersonMesh->CreateAndSetMaterialInstanceDynamic(0);
		//PersonMeshDynamicMaterial = PersonMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, PersonMesh->GetMaterial(0));

		//Create new material instance and assign it
		//PersonMeshDynamicMaterial = UMaterialInstanceDynamic::Create(PersonMesh->GetMaterial(0), this);
		//PersonMesh->SetMaterial(0, PersonMeshDynamicMaterial);


		//PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}
	*/

	//~~ Pedestal Mesh ~~//
	PedestalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedestalMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PedestalMeshObj(TEXT("StaticMesh'/Game/Meshes/Cylinder_Brush_StaticMesh.Cylinder_Brush_StaticMesh'"));
	if (PedestalMeshObj.Succeeded())
	{
		PedestalMesh->SetStaticMesh(PedestalMeshObj.Object);
		PedestalMesh->Mobility = EComponentMobility::Movable;
		PedestalMesh->AttachParent = RootComponent;
	}

	//~~ Pedestal Material ~~//




	//~~ MoveTimeline ~~//
	//MoveTimeLine = FTimeline();
	MoveTimeLine.SetTimelineLength(1);
	//MoveTimeLine.SetPlayRate(1 / 10.f);
	//MoveTimeLine.SetPlaybackPosition(1 / 10.f);


	//~~ Timeline tick update ~~//
	FOnTimelineFloat MoveTimeFloatDelegate = FOnTimelineFloat();
	MoveTimeFloatDelegate.BindUFunction(this, "TimelineUpdate");
	//MoveTimeLine.SetTimelinePostUpdateFunc(MoveTimeEventUpdate);

	//~~ Timeline post update event ~~//
	FOnTimelineEvent MoveTimeEventUpdate = FOnTimelineEvent();
	MoveTimeEventUpdate.BindUFunction(this, "MoveEnded");
	MoveTimeLine.SetTimelineFinishedFunc(MoveTimeEventUpdate);

	//~~ Animation curve ~~//
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveObj(TEXT("CurveFloat'/Game/Util/MoveAnimCurve.MoveAnimCurve'"));
	if (CurveObj.Succeeded())
	{
		MoveCurve = CurveObj.Object;
		MoveTimeLine.AddInterpFloat(MoveCurve, MoveTimeFloatDelegate, FName("Percentage_Complete"));
	}


	FST_StatModifier StarvingEduranceModifier;
	StarvingEduranceModifier.Id = "StarvingEdurance";
	StarvingEduranceModifier.Description = "";
	StarvingEduranceModifier.Amount = 0;
	StatModifiers.Add(StarvingEduranceModifier);

	FST_StatModifier StarvingConfidenceModifier;
	StarvingConfidenceModifier.Id = "StarvingConfidense";
	StarvingConfidenceModifier.Description = "";
	StarvingConfidenceModifier.Amount = 0;
	StatModifiers.Add(StarvingConfidenceModifier);

	//StatModifiers.Add(FST_StatModifier{ "Endurance", "", 0 });
	//StatModifiers.Add(FST_StatModifier{ "Endurance", "", 0 });
	//StatModifiers.Add(FST_StatModifier{ "Cognitive", "", 0});


}


/******************** TimelineUpdate *************************/
void AIslandPerson::TimelineUpdate(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("EFFECT PROGRESS") + FString::SanitizeFloat(Value));
	FVector NewLocation = FMath::Lerp(MoveFromLocation, MoveToLocation, Value);
	SetActorLocation(NewLocation);
}


/******************** MoveEnded *************************/
void AIslandPerson::MoveEnded()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Timeline ended"));
	if (PathToTake.Num() > 0)
	{
		ExecuteMoveAlongPath();
	}
	else 
	{
		if (TilePlacedOn)
		{
			TilePlacedOn->CheckTile();
			// Trigger tile modal
			UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
			if (GameInstance)
			{
				GameInstance->OnPersonMoveEnded.Broadcast(this, TilePlacedOn);
			}
		}
		UpdatePathingOptions(); // force update tiles in range
		PersonState = EIslandPersonState::Idle;
	}
}


/******************** MoveTo *************************/
void AIslandPerson::MoveTo(AIslandTile* Tile) {
	if (Tile)
	{
		MoveFromLocation = GetActorLocation();
		//MoveToLocation = Tile->GetActorLocation();
		MoveToLocation = Tile->PlacePerson(this, false, true);
		//~~ Start animation timeline ~~//
		MoveTimeLine.PlayFromStart();
	}
}


/******************** PersonClicked *************************/
void AIslandPerson::PersonClicked() {
	//UE_LOG(LogTemp, Log, TEXT("pawn clicked"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandPerson:PersonClicked");
	/*
	AIslandPlayerController* PlayerController = Cast<AIslandPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		PlayerController->CenterCameraAt(GetActorLocation());
	}
	*/
	if (TilePlacedOn)
	{
		TilePlacedOn->TileClicked();
	}
	SelectPerson();
}


/******************** SelectPerson *************************/
void AIslandPerson::SelectPerson() {
	if (PersonMeshDynamicMaterial)
	{
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Yellow);
		UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->OnPersonSelected.Broadcast(this);
			Selected = true;
			UpdatePathingOptions();
		}
	}
}


/******************** UpdatePathingOptions *************************/
void AIslandPerson::UpdatePathingOptions() {
	if (TilePlacedOn)
	{
		// Deselect all tile
		for (TActorIterator<AIslandTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			AIslandTile* Tile = *ActorItr;
			Tile->DeselectTile();
			Tile->DistanceFromSelectedPerson = 9999;
		}

		TileRangeMap.Empty();
		TArray<AIslandTile*> VisitedTiles;
		TArray<AIslandTile*> Frontier;
		Frontier.Add(TilePlacedOn);
		TileRangeMap.Add(0, Frontier); //~~ Add base for the start ~~//
		VisitedTiles.Add(TilePlacedOn); //~~ Add base to allready visited to prevent bounce back ~~//

		TilePlacedOn->DistanceFromSelectedPerson = 0; //~~ set person distance to zero on base tile ~~//

		for (int32 k = 0; k < MovePointsLeft; k++)
		{
			TArray<AIslandTile*> NewFrontier;
			TileRangeMap.Add(k + 1, NewFrontier);
			Frontier = TileRangeMap[k];
			//~~ Loop though all tiles in current frontier ~~//
			for (int32 m = 0; m < Frontier.Num(); m++)
			{
				AIslandTile* Tile = Frontier[m];
				//~~ Loop though all Paths connected to this tile to create the next frontier ~~//
				for (int32 l = 0; l < Tile->Paths.Num(); l++)
				{
					AIslandPath* Path = Tile->Paths[l];
					//~~ Error handing in path pointer ~~//
					if (!Path->TileA || !Path->TileB || !Path->bVisible)
					{
						continue; //~~ Skip path ~~//
					}
					// If not oneway or if oneway and This til is A (A=>B)
					if ((Path->bOneWay && Path->TileA == Tile) || !Path->bOneWay)
					{
						AIslandTile* NeighbourTile = nullptr;
						if (Path->TileA == Tile)
						{
							NeighbourTile = Path->TileB;
						}
						else if (Path->TileB == Tile)
						{
							NeighbourTile = Path->TileA;
						}
						if (NeighbourTile)
						{
							if (NeighbourTile && !VisitedTiles.Contains(NeighbourTile))
							{
								NeighbourTile->DistanceFromSelectedPerson = k + 1;
								TileRangeMap[k + 1].Add(NeighbourTile); //~~ Add Neighbor tile to the next frontier ~~//
								VisitedTiles.Add(NeighbourTile); //~~ Add to visited, so that neighbors don't overlap each other. ~~//
							}
						}
					}
				}
				/*
				//~~ Loop though all pathto to create the next frontier ~~//
				for (int32 l = 0; l < Tile->PathTo.Num(); l++)
				{
					AIslandTile* NeighbourTile = Tile->PathTo[l];
					//~~ Check if add to next frontier ~~//
					if (NeighbourTile && !VisitedTiles.Contains(NeighbourTile))
					{
						NeighbourTile->DistanceFromSelectedPerson = k + 1;
						TileRangeMap[k + 1].Add(NeighbourTile); //~~ Add Neighbor tile to the next frontier ~~//
						VisitedTiles.Add(NeighbourTile); //~~ Add to visited, so that neighbors don't overlap each other. ~~//
					}
				}
				*/
			}

		}

		// Select tiles in range
		for (auto& Tiles : TileRangeMap)
		{
			for (int32 i = 0; i < Tiles.Value.Num(); i++)
			{
				AIslandTile* Tile = Tiles.Value[i];
				Tile->SelectTile();
			}
		}
	}
}


/******************** UpdateShortestPath *************************/
void AIslandPerson::UpdateShortestPath(AIslandTile* TargetTile) {
	if (TilePlacedOn && TargetTile)
	{
		PathToTake.Empty();
		int32 ShortestPathLength = 0;
		for (auto& Tiles : TileRangeMap)
		{
			if (Tiles.Value.Find(TargetTile) != -1)
			{
				ShortestPathLength = Tiles.Key;
				break;
			}
		}
		AIslandTile* Tile = TargetTile;
		for (int32 steps = 0; steps < ShortestPathLength; steps++)
		{
			for (int32 i = 0; i < Tile->Paths.Num(); i++)
			{
				AIslandPath* Path = Tile->Paths[i];
				if (!Path->TileA || !Path->TileB)
				{
					continue; //~~ Skip path ~~//
				}
				if ((Path->bOneWay && Path->TileB == Tile) || !Path->bOneWay)
				{
					AIslandTile* NeighbourTile = nullptr;
					if (Path->TileA == Tile)
					{
						NeighbourTile = Path->TileB;
					}
					else if (Path->TileB == Tile)
					{
						NeighbourTile = Path->TileA;
					}
					if (NeighbourTile)
					{
						if (NeighbourTile->DistanceFromSelectedPerson < Tile->DistanceFromSelectedPerson)
						{
							if (Tile->DistanceFromSelectedPerson > 0)
							{
								PathToTake.Insert(Tile, 0);
								Tile = NeighbourTile;
								i = -1; // Reset neighbour loop for new current tile
							}
							else
							{
								PathToTake.Insert(Tile, 0);
								// We are there
								break;
							}
						}
					}
				}
			}
			/*
			for (int32 i = 0; i < Tile->PathTo.Num(); i++)
			{
				AIslandTile* NeighbourTile = Tile->PathTo[i];
				//~~ If neighbour tile distance from person is lower than current tile ~~//
				if (NeighbourTile->DistanceFromSelectedPerson < Tile->DistanceFromSelectedPerson)
				{
					if (Tile->DistanceFromSelectedPerson > 0)
					{
						PathToTake.Insert(Tile, 0);
						Tile = NeighbourTile;
						i = -1; // Reset neighbour loop for new current tile
					}
					else 
					{
						PathToTake.Insert(Tile, 0); 
						// We are there
						break;
					}
				}
			}
			*/
		}
	}
}


/******************** ExecuteMoveAlongPath *************************/
void AIslandPerson::ExecuteMoveAlongPath()
{
	if (PathToTake.Num() > 0 && PathToTake[0])
	{
		PersonState = EIslandPersonState::Moving;
		// Deselect all tile
		for (TActorIterator<AIslandTile> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
			AIslandTile* Tile = *ActorItr;
			Tile->DeselectTile();
		}

		MoveFromLocation = GetActorLocation();
		MoveToLocation = PathToTake[0]->PlacePerson(this, false, true);
		PathToTake.RemoveAt(0);
		MovePointsLeft--; //~~ Decrease movement points per tile moved ~~//
		MoveTimeLine.PlayFromStart();
	}
}


/******************** OnAnyTileSelected *************************/
void AIslandPerson::OnAnyPersonSelected(AIslandPerson* Person)
{
	if (Person != this)
	{
		if (PersonMeshDynamicMaterial)
		{
			PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::White);
			Selected = false;
		}
	}
}


/******************** OnTurnSwitched *************************/
void AIslandPerson::OnTurnSwitched(float Turn)
{
	if (!bEatenThisTurn)
	{
		TurnsStaving++;
		HungerModifier--;
		// Add negative modifier to all stats
		for (auto& Modifier : StatModifiers)
		{
			//Modifier.Key Modifier stat name
			//Modifier.Value Modifier stat value int
			//PersonRawData.Stats



		}
		//StatModifiers
	}
	else
	{
		//~~ Descrese stat starving modifiers ~~//
		TurnsStaving = 0;
		if (HungerModifier < 0)
		{
			HungerModifier++;
		}
	}
}


/******************** OnNewTurn *************************/
void AIslandPerson::OnNewTurn(float Turn)
{
	//~~ Reset needs ~~//
	bEatenThisTurn = false;
	//~~ Reset movement points ~~//
	MovePointsLeft = 2;

	if (Selected)
	{
		UpdatePathingOptions();
	}
}


// Called when the game starts or when spawned
void AIslandPerson::BeginPlay()
{
	Super::BeginPlay();
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnPersonSelected.AddDynamic(this, &AIslandPerson::OnAnyPersonSelected);
		GameInstance->OnTurnSwitched.AddDynamic(this, &AIslandPerson::OnTurnSwitched);
		GameInstance->OnNewTurn.AddDynamic(this, &AIslandPerson::OnNewTurn);
	}
	if (TilePlacedOn)
	{
		TilePlacedOn->CheckTile();
	}
	/*
	TimeLine.PlayFromStart();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIslandPerson::TickTimeline, DELTATIME, true, 0.0f);
	*/
}



// Called every frame
void AIslandPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//~~ Tick timeline for movement ~~//
	if (MoveTimeLine.IsPlaying())
	{
		MoveTimeLine.TickTimeline(DeltaTime);
	}
}


// Called on spawn actor(PIE) and load actor
void AIslandPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("AIslandPerson::PostInitializeComponents"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandPerson::PostInitializeComponents");
	/*
	if (PersonMeshMaterial)
	{
		PersonMeshDynamicMaterial = UMaterialInstanceDynamic::Create(PersonMeshMaterial, this);
		PersonMesh->SetMaterial(0, PersonMeshDynamicMaterial);
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}
	*/
}


// TODO 
// - Test when PostInitializeComponents is called. Placd in editor. Spawned in play, loaded from disk on startup
// - Test when OnConstruction is called. Placed in editor. C++ prop, uproperty change and blueprint change. Spawned in play, loaded from disk

// Called on spawn actor, and Uproperty value change
void AIslandPerson::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UE_LOG(LogTemp, Warning, TEXT("AIslandPerson::OnConstruction"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "AIslandPerson::OnConstruction");
	if (PersonMeshMaterial)
	{
		PersonMeshDynamicMaterial = UMaterialInstanceDynamic::Create(PersonMeshMaterial, this);
		PersonMesh->SetMaterial(0, PersonMeshDynamicMaterial);
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}

	//!! This will not work. The game instance is only present when in play. !!//
	/*
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		static const FString ContextString(TEXT("GENERAL")); //~~ Key value for each column of values ~~//
		FST_Person* PersonData = GameInstance->DATA_People->FindRow<FST_Person>(*PersonId, ContextString);
		if (PersonData)
		{
			PersonRawData = *PersonData;
		}
	}
	*/

	//~~ Place Person ~~//
	if (TilePlacedOn)
	{
		TilePlacedOn->PlacePerson(this, true, true);
	}

	//~~ Data table read raw data
	UDataTable* PeopleTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/Data/People.People'"));
	if (PeopleTable)
	{
		static const FString ContextString(TEXT("GENERAL")); //~~ Key value for each column of values ~~//
		FST_Person* PersonData = PeopleTable->FindRow<FST_Person>(*PersonId, ContextString);
		if (PersonData)
		{
			PersonRawData = *PersonData;
		}
		else {
			PersonRawData = FST_Person{};
		}
	}
	else
	{
		PersonRawData = FST_Person{};
	}


	//static const FString ContextString(TEXT("GENERAL")); //~~ Key value for each column of values ~~//
	//FST_Structure* StructureData = DATA_Structures->FindRow<FST_Structure>(*RowName, ContextString);
	//if (StructureData)

	//RegisterAllComponents();


	// For creating object in OnConstruction
	/*
	for (int32 i = 0; i < nNbComponentsToSpawn; i++)
	{
	USphereComponent* spawnPoint = NewObject<USphereComponent>(this);
	spawnPoint->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	spawnPoint->AttachParent = RootComponent;
	spawnPoint->bCastDynamicShadow = false;
	spawnPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	RegisterAllComponents();
	*/
}


//PostEditMove

//PostEditChangeProperty 