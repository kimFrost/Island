// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "IslandHUD.h"
#include "IslandCharacter.h"
#include "IslandPlayerController.generated.h"




//~~~~~ ENUMS ~~~~~//

UENUM(BlueprintType)
enum class EToolType : uint8
{
	Select UMETA(DisplayName = "Select"),
	Move UMETA(DisplayName = "Move")
};



/**
 * 
 */
UCLASS()
class ISLAND_API AIslandPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AIslandPlayerController(const FObjectInitializer &ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
	EToolType ActiveToolType;

	// Selected Tile

	// Selected Person

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool")
	AActor* SelectedActor;

	//~~ Inputs ~~//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool LeftMouseButtonDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool RightMouseButtonDown;


protected:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void LeftClickPressed();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void LeftClickReleased();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void RightClickPressed();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void RightClickReleased();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Zoom(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TestFunction();


protected:

	//~~ Input setup ~~//
	virtual void SetupInputComponent() override;


public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;


};
