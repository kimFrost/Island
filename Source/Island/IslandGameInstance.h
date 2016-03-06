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
//class APOTLStructure;



//~~~~~ Delegates/Event dispatcher ~~~~~//
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurnSwitched, float, Turn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewTurn, float, Turn);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStructurePlanted, APOTLStructure*, Structure);




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

private:

	// Store the current playstate
	EIslandPlayState CurrentState;


public:

	/*********** FUNCTIONS **************/
	
	//~~ Turn ~~//

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void SwitchTurn();

	UFUNCTION(BlueprintCallable, Category = "Turn")
	void NewTurn(float WaitTime);


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

	//UPROPERTY(BlueprintAssignable, Category = "Structure")
	//FStructurePlanted OnStructurePlanted;

};




FORCEINLINE EIslandPlayState UIslandGameInstance::GetCurrentState() const
{
	return CurrentState;
}