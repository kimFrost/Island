// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandDataHolder.h"
#include "IslandGameInstance.h"



// Sets default values
UIslandGameInstance::UIslandGameInstance(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	ReadTables();


}



/******************** ReadTables *************************/
void UIslandGameInstance::ReadTables()
{
	//~~ People ~~//
	UDataTable* PeopleTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/Data/People.People'"));
	if (PeopleTable)
	{
		DATA_People = PeopleTable;
	}
	//~~ Cards ~~//
	UDataTable* CardsTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/Data/Cards.Cards'"));
	if (CardsTable)
	{
		DATA_Cards = CardsTable;
	}
	//~~ Events ~~//
	UDataTable* EventsTable = (UDataTable*)StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("DataTable'/Game/Data/Events.Events'"));
	if (EventsTable)
	{
		DATA_Events = EventsTable;
	}
}


/******************** SetCurrentState *************************/
void UIslandGameInstance::SetCurrentState(EIslandPlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);
}


/******************** HandleNewState *************************/
void UIslandGameInstance::HandleNewState(EIslandPlayState NewState)
{
	switch (NewState)
	{
		case EIslandPlayState::EPlaying:
		{
			
		}
		break;
		case EIslandPlayState::EGameOver:
		{
		}
		break;
		case EIslandPlayState::EUnknown:
		// Do nothing
		break;
	}
}