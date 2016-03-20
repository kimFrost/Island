// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.generated.h"


//~~~~~ ENUMS ~~~~~//

// Enum to store the current state of gameplay
enum class EIslandPlayState : uint8 //** you can replace short with uint8 */
{
	EPlaying,
	EGameOver,
	EUnknown
};



//~~~~~ Forward Declarations ~~~~~//
class AIslandTile;
class AIslandPerson;



//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurnSwitched, float, Turn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewTurn, float, Turn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileClicked, AIslandTile*, Tile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileRevealed, AIslandTile*, Tile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPersonSelected, AIslandPerson*, Person);





/**
 * 
 */
UCLASS()
class ISLAND_API UIslandGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	// Sets default values for this's properties
	UIslandGameInstance(const FObjectInitializer &ObjectInitializer);
	
	EIslandPlayState GetCurrentState() const;
	
	//~~ Data ~~//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	UDataTable* DATA_People;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	UDataTable* DATA_Cards;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data")
	UDataTable* DATA_Events;

	//~~ Stats ~~//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turn")
	int32 CurrentTurn;


private:

	// Store the current playstate
	EIslandPlayState CurrentState;


public:

	/*********** FUNCTIONS **************/
	
	//~~ Turn ~~//

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void SwitchTurn();

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void NewTurn();

	UFUNCTION(BlueprintCallable, Category = "Turn")
	FST_Card GetRandCard(EIslandCardType Type);

	//~~ Broadcasts ~~//

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void BroadcastClickedTile(AIslandTile* Tile);


	//~~ Cards ~~//

	// GetNewCard


	//~~ Events ~~//

	// GetNewEvent


	//~~ State ~~//

	void SetCurrentState(EIslandPlayState NewState);

	void HandleNewState(EIslandPlayState NewState);


	//~~ Data ~~//

	UFUNCTION(BlueprintCallable, Category = "Data")
	void ReadTables();


	/*********** DELEGATES **************/

	UPROPERTY(BlueprintAssignable, Category = "Turn")
	FTurnSwitched OnTurnSwitched;

	UPROPERTY(BlueprintAssignable, Category = "Turn")
	FNewTurn OnNewTurn;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FTileClicked OnTileClicked;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FTileRevealed OnTileRevealed;

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FPersonSelected OnPersonSelected;

	//UPROPERTY(BlueprintAssignable, Category = "Structure")
	//FStructurePlanted OnStructurePlanted;

};




FORCEINLINE EIslandPlayState UIslandGameInstance::GetCurrentState() const
{
	return CurrentState;
}