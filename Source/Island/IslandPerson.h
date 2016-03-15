// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandDataHolder.h"
#include "IslandPerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;


UCLASS()
class ISLAND_API AIslandPerson : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandPerson(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FST_Person PersonRawData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString PersonId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	int32 ActionsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	bool Selected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	AIslandTile* TilePlacedOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* PersonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInstance* PersonMeshMaterial;
	//UMaterial* PersonMeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInstanceDynamic* PersonMeshDynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* PedestalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInstanceDynamic* PedestalMeshDynamicMaterial;




	// TimeLine

	UPROPERTY(EditInstanceOnly, Category = "Animation")
	FTimeline MoveTimeLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UCurveFloat* MoveCurve;

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	FOnTimelineEvent MoveTimelineEventEvent;
 
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FOnTimelineFloat MoveTimelineFloatEvent;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FVector MoveFromLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FVector MoveToLocation;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void TimelineUpdate(float Value);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void MoveEnded();
	


 



	/*********** FUNCTIONS **************/

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveTo(AIslandTile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void PersonClicked();

	UFUNCTION(BlueprintCallable, Category = "Person")
	void SelectPerson();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnAnyPersonSelected(AIslandPerson* Person);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
};
