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

UENUM(BlueprintType)
enum class EIslandCardType : uint8
{
	Event UMETA(DisplayName = "Event"),
	Tile UMETA(DisplayName = "Tile")
};

UENUM(BlueprintType)
enum class ETileActions : uint8
{
	Explore UMETA(DisplayName = "Explore"),
	Event UMETA(DisplayName = "Event"),
	GiveItem UMETA(DisplayName = "Give item"),
	DoNothing UMETA(DisplayName = "Do nothing")
};

UENUM(BlueprintType)
enum class ETileStdActions : uint8
{
	DoNothing UMETA(DisplayName = "Do nothing")
};


//~~~~~ DATA IMPORT ~~~~~//


USTRUCT(BlueprintType)
struct FST_Item : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Item()
		: Title(TEXT("No title"))
		, Description(TEXT("No Description"))
		, Unique(false)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool Unique;
};


USTRUCT(BlueprintType)
struct FST_Effect : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Effect()
		: Prop(TEXT("No name"))
		, Value(0)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FString Prop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	int32 Value;
};


USTRUCT(BlueprintType)
struct FST_Trait : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Trait()
		: Title(TEXT("No title"))
		, Description(TEXT("No Description"))
		, Effects(TArray<FST_Effect>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FString Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	TArray<FST_Effect> Effects;
};


USTRUCT(BlueprintType)
struct FST_Person : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Person()
		: Id(TEXT(""))
		, Title(TEXT("No title"))
		, Description(TEXT("No description"))
		, Profession(TEXT("No profession"))
		, Traits(TArray<FST_Trait>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString Profession; //?? Maybe a enum instead? ??//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<FST_Trait> Traits;
};

//TEnumAsByte<EElementalEnum::Type> PrimaryElementalType;




USTRUCT(BlueprintType)
struct FST_Stats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Stats()
		: Confidence(1)
		, Cognitive(1)
		, Endurance(1)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Confidence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Cognitive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Endurance;
};

// Motivations
// Relationships
// Secrets
// Hobbies



USTRUCT(BlueprintType)
struct FST_Action : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Action()
		: Title(TEXT("No title"))
		, Type(ETileActions::DoNothing)
		, Conditions(TArray<FString>())
		, NotConditions(TArray<FString>())
		, Events(TArray<FString>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	ETileActions Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> NotConditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> Events;
};


USTRUCT(BlueprintType)
struct FST_Card : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Card()
		: Id(TEXT(""))
		, Title(TEXT("No title"))
		, Items(TArray<FString>())
		, Actions(TArray<FST_Action>())
		, IdleActions(TArray<FST_Action>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FString> Items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FST_Action> Actions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<FST_Action> IdleActions;
};

//TAssetPtr<UTexture> AchievementIcon; "Texture2d'/Game/Textures/AchievementIcon2'"



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