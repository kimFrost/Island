// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "IslandCharacter.h"
#include "IslandPlayerController.h"



AIslandGameMode::AIslandGameMode(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/

	//Blueprint'/Game/Blueprints/HUD/BP_HUD.BP_HUD'

	//~~ Set the default HUD ~~ //
	static ConstructorHelpers::FClassFinder<AIslandHUD> HUDBPClass(TEXT("/Game/Blueprints/HUD/BP_HUD"));
	if (HUDBPClass.Class)
	{
		HUDClass = HUDBPClass.Class;
	}
	else 
	{
		HUDClass = AIslandHUD::StaticClass();
	}

	//~~ Set the default PlayerController ~~ //
	static ConstructorHelpers::FClassFinder<AIslandPlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/PlayerController/BP_PlayerController"));
	if (PlayerControllerBPClass.Class)
	{
		//PlayerControllerClass = PlayerControllerBPClass.Class;
		PlayerControllerClass = AIslandPlayerController::StaticClass();
	}
	else
	{
		PlayerControllerClass = AIslandPlayerController::StaticClass();
	}

	//~~ Set the default Character ~~ //
	static ConstructorHelpers::FClassFinder<AIslandCharacter> CharacterBPClass(TEXT("/Game/Blueprints/Characters/BP_Character"));
	if (CharacterBPClass.Class)
	{
		DefaultPawnClass = CharacterBPClass.Class;
		//DefaultPawnClass = AIslandCharacter::StaticClass();
	}
	else
	{
		DefaultPawnClass = AIslandCharacter::StaticClass();
	}



	//GameStateClass
	//PlayerStateClass
	//SpectatorClass
}



void AIslandGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AIslandGameMode::BeginPlay()
{
	Super::BeginPlay();

}