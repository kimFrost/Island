// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.h"
#include "IslandPlayerController.h"
#include "IslandTile.h"
#include "IslandPerson.h"


// Sets default values
AIslandPerson::AIslandPerson(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActionsLeft = 0;
	Selected = false;

	OnClicked.AddDynamic(this, &AIslandPerson::PersonClicked);

	TilePlacedOn = nullptr;


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



	//~~ Animation curve ~~//
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveObj(TEXT("CurveFloat'/Game/OwnStuff/EffectCurve.EffectCurve'"));
	if (CurveObj.Succeeded())
	{
		//TimeLine = FTimeline{};
		//FOnTimelineFloat progressFunction{};
		//progressFunction.BindUFunction(this, "EffectProgress");
		//TimeLine.AddInterpFloat(Curve.Object, progressFunction);
	}

}






/** The function which gets called from the timeline tick */
void AIslandPerson::EffectProgress(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("EffectProgress: timeline: %f  value:%f"), TimeLine.GetPlaybackPosition(), Value));
	// do something

}

/** Function which gets called from the Timer to call EffectProgress */
void AIslandPerson::TickTimeline()
{
	if (TimeLine.IsPlaying())
	{
		TimeLine.TickTimeline(DELTATIME);
	}
	else
	{
		//GetWorldTimerManager().ClearTimer(this, &AIslandPerson::TickTimeline);
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SetLifeSpan(0);
	}
}






/******************** MoveTo *************************/
void AIslandPerson::MoveTo(AIslandTile* Tile) {

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


/******************** PersonClicked *************************/
void AIslandPerson::SelectPerson() {
	if (PersonMeshDynamicMaterial)
	{
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Yellow);
		UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->OnPersonSelected.Broadcast(this);
			Selected = true;
		}
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



// Called when the game starts or when spawned
void AIslandPerson::BeginPlay()
{
	Super::BeginPlay();
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnPersonSelected.AddDynamic(this, &AIslandPerson::OnAnyPersonSelected);
	}
	


	TimeLine.PlayFromStart();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIslandPerson::TickTimeline, DELTATIME, true, 0.0f);
}


// Called every frame
void AIslandPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AIslandPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	/*
	if (PersonMeshMaterial)
	{
		PersonMeshDynamicMaterial = UMaterialInstanceDynamic::Create(PersonMeshMaterial, this);
		PersonMesh->SetMaterial(0, PersonMeshDynamicMaterial);
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}
	*/
}


void AIslandPerson::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

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
		TilePlacedOn->PlacePerson(this, true);
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


}


//PostEditMove

//PostEditChangeProperty 