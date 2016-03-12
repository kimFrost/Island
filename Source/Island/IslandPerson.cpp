// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.h"
#include "IslandPlayerController.h"
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
	}
	PersonMesh->AttachParent = RootComponent;



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
	static ConstructorHelpers::FObjectFinder<UStaticMesh>PedestalMeshObj(TEXT("StaticMesh'/Game/Meshes/Cylinder_Brush_StaticMesh.Cylinder_Brush_StaticMesh'"));
	if (PedestalMeshObj.Succeeded())
	{
		PedestalMesh->SetStaticMesh(PedestalMeshObj.Object);
	}
	PedestalMesh->AttachParent = RootComponent;

	//~~ Pedestal Material ~~//




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
	UIslandGameInstance* GameInstance = Cast<UIslandGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->OnPersonSelected.Broadcast(this);
		if (PersonMeshDynamicMaterial)
		{
			SelectPerson();
		}
	}
}


/******************** PersonClicked *************************/
void AIslandPerson::SelectPerson() {
	PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Yellow);
}

/******************** OnAnyTileSelected *************************/
void AIslandPerson::OnAnyPersonSelected(AIslandPerson* Person)
{
	if (Person != this)
	{
		if (PersonMeshDynamicMaterial)
		{
			PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::White);
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
	
}

// Called every frame
void AIslandPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIslandPerson::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (PersonMeshMaterial)
	{
		PersonMeshDynamicMaterial = UMaterialInstanceDynamic::Create(PersonMeshMaterial, this);
		PersonMesh->SetMaterial(0, PersonMeshDynamicMaterial);
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}
}



void AIslandPerson::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Better with dynamic material here???



	//static const FString ContextString(TEXT("GENERAL")); //~~ Key value for each column of values ~~//
	//FST_Structure* StructureData = DATA_Structures->FindRow<FST_Structure>(*RowName, ContextString);
	//if (StructureData)


}