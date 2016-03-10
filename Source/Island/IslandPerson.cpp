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



	//StaticMesh'/Game/Meshes/SM_TestPerson.SM_TestPerson'
	//StaticMesh'/Game/Meshes/Cylinder_Brush_StaticMesh.Cylinder_Brush_StaticMesh'

	// 0, 70, 260


	USceneComponent* const TranslationComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	TranslationComp->Mobility = EComponentMobility::Movable;
	RootComponent = TranslationComp;


	//~~ Person Mesh ~~//
	PersonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PersonMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>PersonMeshObj(TEXT("StaticMesh'/Game/Meshes/SM_TestPerson.SM_TestPerson'"));
	if (PersonMeshObj.Succeeded())
	{
		PersonMesh->SetStaticMesh(PersonMeshObj.Object);
	}
	PersonMesh->AttachParent = RootComponent;

	//~~ Person Material ~~//
	static ConstructorHelpers::FObjectFinder<UMaterialInstance>MaterialInstanceObj(TEXT("MaterialInstanceConstant'/Game/Materials/Selected/M_SelectedTest_Inst.M_SelectedTest_Inst'"));
	if (PersonMesh && MaterialInstanceObj.Succeeded())
	{
		PersonMesh->SetMaterial(0, MaterialInstanceObj.Object);
		PersonMeshDynamicMaterial = PersonMesh->CreateDynamicMaterialInstance(0, PersonMesh->GetMaterial(0));
		PersonMeshDynamicMaterial->SetVectorParameterValue("ParamColor", FLinearColor::Red);
	}

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

