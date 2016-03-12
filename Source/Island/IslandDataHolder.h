// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IslandDataHolder.generated.h"



//~~~~~ Forward Declarations ~~~~~//
//class APOTLStructure;


//~~~~~ ENUMS ~~~~~//

UENUM(BlueprintType)
enum class EPersonTypesEnum : uint8
{
	Boy UMETA(DisplayName = "Boy"),
	Girl UMETA(DisplayName = "Girl"),
	Man UMETA(DisplayName = "Man"),
	Women UMETA(DisplayName = "Women"),
	OldMan UMETA(DisplayName = "OldMan"),
	OldWomen UMETA(DisplayName = "OldWomen")
};



//~~~~~ DATA IMPORT ~~~~~//

USTRUCT(BlueprintType)
struct FST_Ingredient
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	int32 Quantity;
	FST_Ingredient()
		: Id(FName(TEXT("")))
		, Quantity(0)
	{}
};


USTRUCT(BlueprintType)
struct FST_ResourceRecipe : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_ResourceRecipe()
		//: Wood(0.f)
		//, Planks(0.f)
	{}
	UPROPERTY(EditAnywhere, Category = "Resources")
	TArray<FST_Ingredient> Ingredients;
	UPROPERTY(EditAnywhere, Category = "Resources")
	int32 Servings;
	UPROPERTY(EditAnywhere, Category = "Resources")
	int32 Sequence;
};


USTRUCT(BlueprintType)
struct FST_Person : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Person()
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString Title;
};


USTRUCT(BlueprintType)
struct FST_Card : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Card()
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Title;
};


USTRUCT(BlueprintType)
struct FST_Event : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Event()
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FString Title;
};


//~~~~~ STRUCTS ~~~~~//




/*** FST_Point ***/
USTRUCT(BlueprintType)
struct FST_Point
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	int32 Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	int32 Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	bool IsCreator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	bool Exits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	int32 Hex0Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	int32 Hex1Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	int32 Hex2Index;

	FST_Point()
	{
		Location = { -1, -1, -1 };
		Column = 0;
		Row = 0;
		IsCreator = false;
		Exits = false;
		Hex0Index = -1;
		Hex1Index = -1;
		Hex2Index = -1;
	}
};



UCLASS()
class ISLAND_API UIslandDataHolder : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UIslandDataHolder(const FObjectInitializer& ObjectInitializer);

};


/*
class ISLAND_API IslandDataHolder
{
public:
	IslandDataHolder();
	~IslandDataHolder();
};
*/