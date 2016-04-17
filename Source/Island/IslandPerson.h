// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "IslandDataHolder.h"
#include "IslandPerson.generated.h"


//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;


//~~~~~ ENUMS ~~~~~//
UENUM(BlueprintType)
enum class EIslandPersonState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA(DisplayName = "Moving"),
	Trapped UMETA(DisplayName = "Trapped")
};



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
	int32 MovePointsLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	EIslandPersonState PersonState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	bool Selected;

	bool bEatenThisTurn;
	
	bool bAvaiable;

	int32 TurnsStaving;

	FST_Modifier HungerModifier;

	TArray<FST_Modifier> Modifiers;


	//UPROPERTY(BlueprintReadOnly, Category = "Person")
	//TMap<EPersonStat, FST_Stat> PersonStats;
	TMap<EPersonStat, int32> PersonStats;
	//FST_Stats PersonStats;

	//UPROPERTY(BlueprintReadOnly, Category = "Person")
	TMap<EPersonStat, EStatStates> PersonStatStates;
	//FST_StatState PersonStatStates;

	UFUNCTION(BlueprintCallable, Category = "Person")
	void UpdateStats();

	UFUNCTION(BlueprintCallable, Category = "Person")
	TArray<FST_Stat> GetPersonStats() const;

	UFUNCTION(BlueprintCallable, Category = "Person")
	EStatStates GetStatState(EPersonStat Stat) const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	AIslandTile* TilePlacedOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	AIslandTile* TestTileRef;

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

	TMap<int32, TArray<AIslandTile*>> TileRangeMap;



	// TimeLine

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation") //!! Cannot be a UPROPERTY, the update function won't run, for some reason !!//
	FTimeline MoveTimeLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UCurveFloat* MoveCurve;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FVector MoveFromLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	FVector MoveToLocation;

	UFUNCTION()
	void TimelineUpdate(float Value);
	
	UFUNCTION()
	void MoveEnded();
	

	// Path

	TArray<AIslandTile*> PathToTake;




	/*********** FUNCTIONS **************/

	

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveTo(AIslandTile* Tile);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void PersonClicked();

	UFUNCTION(BlueprintCallable, Category = "Person")
	void SelectPerson();

	UFUNCTION(BlueprintCallable, Category = "Pathing")
	void UpdatePathingOptions();

	UFUNCTION(BlueprintCallable, Category = "Pathing")
	void UpdateShortestPath(AIslandTile* TargetTile);

	UFUNCTION(BlueprintCallable, Category = "Pathing")
	void ExecuteMoveAlongPath();

	UFUNCTION(BlueprintCallable, Category = "Person")
	void ParseTraits();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnAnyPersonSelected(AIslandPerson* Person);

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void OnTurnSwitched(float Turn);

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void OnNewTurn(float Turn);


	void TimerExpired();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void PostInitializeComponents() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
};




//~~ Getters ~~//
FORCEINLINE TArray<FST_Stat> AIslandPerson::GetPersonStats() const
{
	TArray<FST_Stat> Stats;
	for (auto& Stat : PersonStats)
	{
		Stats.Add({ Stat.Key, Stat.Value });
	}
	return Stats;
}

FORCEINLINE EStatStates AIslandPerson::GetStatState(EPersonStat Stat) const
{
	return PersonStatStates[Stat];
}


//~~ Setters ~~//