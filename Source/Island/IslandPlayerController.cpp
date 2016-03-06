// Fill out your copyright notice in the Description page of Project Settings.

#include "Island.h"
#include "IslandHUD.h"
#include "IslandCharacter.h"
#include "IslandPlayerController.h"




// Sets default values
AIslandPlayerController::AIslandPlayerController(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	ActiveToolType = EToolType::Select;
	SelectedActor = nullptr;
	bShowMouseCursor = true;
	
}




//~~ Input functions ~~//

/******************** LeftClickPressed *************************/
void AIslandPlayerController::LeftClickPressed()
{
	LeftMouseButtonDown = true;
	
}

/******************** LeftClickReleased *************************/
void AIslandPlayerController::LeftClickReleased()
{
	LeftMouseButtonDown = false;
}


/******************** LeftClickPressed *************************/
void AIslandPlayerController::RightClickPressed()
{
	RightMouseButtonDown = true;
}


/******************** LeftClickReleased *************************/
void AIslandPlayerController::RightClickReleased()
{
	RightMouseButtonDown = false;
}


/******************** Zoom *************************/
void AIslandPlayerController::Zoom(float Value)
{
	if (Value != 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "PC:Zoom" + FString::FromInt(FMath::RoundToInt(Value)));
		//GetControlledPawn()->AddControllerPitchInput(Value * 10.f);
		AIslandCharacter* Character = Cast<AIslandCharacter>(GetControlledPawn());
		if (Character)
		{
			Character->CameraBoom->TargetArmLength += Value * 100.f; 
		}
	}
}


/******************** TestFunction *************************/
void AIslandPlayerController::TestFunction()
{
	//UE_LOG(LogTemp, Log, TEXT("PC:TestFunction"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "PC:TestFunction");
	//GetControlledPawn()->AddControllerYawInput();
}



/******************** SetupPlayerInputComponent *************************/
void AIslandPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Set up gameplay key bindings
	check(InputComponent);

	//~~ Mouse ~~//
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AIslandPlayerController::LeftClickPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AIslandPlayerController::LeftClickReleased);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &AIslandPlayerController::RightClickPressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &AIslandPlayerController::RightClickReleased);

	InputComponent->BindAxis("Zoom", this, &AIslandPlayerController::Zoom);

	//InputComponent->BindAxis
	//InputComponent->BindKey(EKeys::A, IE_Released, this, &AIslandPlayerController::TestFunction);
	//InputComponent->BindKey(EMouseButtons::Left, IE_Released, this, &AIslandPlayerController::TestFunction);
}


void AIslandPlayerController::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(this);

}


void AIslandPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

