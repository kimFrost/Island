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
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}





/******************** CenterCameraAt *************************/
void AIslandPlayerController::CenterCameraAt(FVector WorldPosition)
{
	GetPawn()->SetActorLocation(WorldPosition + FVector(0, 0, 500));



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

	if (!GetWorld())
	{
		return;
	}
	
	// Trace
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	//RV_TraceParams.TraceTag = TraceTag;

	//~~ Re-initialize hit info ~~//
	FHitResult RV_Hit(ForceInit);

	FVector WorldLocation;
	FVector WorldDirection;
	this->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	//FRotator currentCharacterRotation = this->GetActorRotation();
	//FRotator targetRotation = mouseDirection.Rotation();

	//WorldLocation = WorldLocation + LandscapeLocation;

	FVector LineTraceFrom = WorldLocation + FVector{ 1.f, 1.f, 0.f };
	FVector LineTraceTo = WorldDirection * 50000 + WorldLocation + FVector{ 1.f, 1.f, 0.f };

	//ECC_GameTraceChannel1
	
	//this->GetWorld()->LineTraceSingleByChannel(RV_Hit, LineTraceFrom, LineTraceTo, ChannelLandscape, RV_TraceParams);
	this->GetWorld()->LineTraceSingleByChannel(RV_Hit, LineTraceFrom, LineTraceTo, ECC_Pawn, RV_TraceParams);
	if (RV_Hit.bBlockingHit)
	{
		if (RV_Hit.GetActor())
		{
			AIslandTile* HitTile = Cast<AIslandTile>(RV_Hit.GetActor());
			if (HitTile)
			{
				if (ActiveToolType == EToolType::Select)
				{

				}
			}
			AIslandPerson* HitPerson = Cast<AIslandPerson>(RV_Hit.GetActor());
			if (HitPerson)
			{
				if (ActiveToolType == EToolType::Select)
				{

				}
			}
		}
	}
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
		AIslandCharacter* Character = Cast<AIslandCharacter>(GetPawn());
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




	//const FInputChord Chord,
	//const EInputEvent KeyEvent,
	//UserClass * Object,
	//typename FInputActionHandlerSignature::TUObjectMethodDelegate< UserClass >::FMethodPtr Func

	/*
	InputComponent->BindKey(EMouseButtons::Left, IE_Pressed, this, &AIslandPlayerController::LeftClickPressed);
	InputComponent->BindKey(EMouseButtons::Left, IE_Released, this, &AIslandPlayerController::LeftClickReleased);
	InputComponent->BindKey(EMouseButtons::Right, IE_Pressed, this, &AIslandPlayerController::RightClickPressed);
	InputComponent->BindKey(EMouseButtons::Right, IE_Released, this, &AIslandPlayerController::RightClickReleased);
	*/
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

