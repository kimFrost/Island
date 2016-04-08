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

/*
UENUM(BlueprintType)
enum class EStats : uint8
{
Confidence UMETA(DisplayName = "Confidence"),
Confidence UMETA(DisplayName = "Confidence")
};
*/

UENUM(BlueprintType)
enum class EEffectTarget : uint8
{
	Self UMETA(DisplayName = "Self"),
	TileAll UMETA(DisplayName = "All on tile"),
	TileOne UMETA(DisplayName = "One on tile")
};

UENUM(BlueprintType)
enum class EEffectProp : uint8
{
	None UMETA(DisplayName = "None"),
	Confidence UMETA(DisplayName = "Confidence"),
	Endurance UMETA(DisplayName = "Endurance"),
	Cognitive UMETA(DisplayName = "Cognitive")
};

UENUM(BlueprintType)
enum class EPersonStat : uint8
{
	None UMETA(DisplayName = "None"),
	Confidence UMETA(DisplayName = "Confidence"),
	Endurance UMETA(DisplayName = "Endurance"),
	Cognitive UMETA(DisplayName = "Cognitive")
};

UENUM(BlueprintType)
enum class EStatStates : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Boosted UMETA(DisplayName = "Boosted"),
	Weakened UMETA(DisplayName = "Weakened"),
	Nullified UMETA(DisplayName = "Nullified")
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
		: Prop(EEffectProp::None)
		, Quantity(0)
		, Target(EEffectTarget::Self)
		, Turns(1)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	EEffectProp Prop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	EEffectTarget Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	int32 Turns;
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
	TArray<FST_Effect> Effects;
};


USTRUCT(BlueprintType)
struct FST_Stat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Stat(EPersonStat Stat = EPersonStat::None, int32 Level = 0)
		: Stat(EPersonStat::None)
		, Level(Level)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EPersonStat Stat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Level;
};


/*
USTRUCT(BlueprintType)
struct FST_Stats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Stats()
		: Confidence(FST_Stat{ "Confidence", 1 })
		, Endurance(FST_Stat{ "Endurance", 1 })
		, Cognitive(FST_Stat{ "Cognitive", 1 })
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FST_Stat Confidence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FST_Stat Endurance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FST_Stat Cognitive;
};
*/


//TEnumAsByte<EElementalEnum::Type> PrimaryElementalType;



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
		, TileId(TEXT(""))
		, Type(ETileActions::DoNothing)
		, Conditions(TArray<FString>())
		, NotConditions(TArray<FString>())
		, ReqStats(TArray<FST_Stat>())
		, Events(TArray<FString>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	FString TileId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	ETileActions Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> Conditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> NotConditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FST_Stat> ReqStats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	TArray<FString> Events;
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
		, Stats(TArray<FST_Stat>())
		, Traits(TArray<FST_Trait>())
		, TileSpecActios(TArray<FST_Action>())
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
	TArray<FST_Stat> Stats;
	//FST_Stats Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<FST_Trait> Traits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Person")
	TArray<FST_Action> TileSpecActios;
};


USTRUCT(BlueprintType)
struct FST_Card : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Card()
		: Id(TEXT(""))
		, Title(TEXT("No title"))
		, TileScene(TEXT(""))
		, Items(TArray<FString>())
		, Actions(TArray<FST_Action>())
		, IdleActions(TArray<FST_Action>())
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString TileScene;
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

USTRUCT(BlueprintType)
struct FST_Map
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Map()
		: Key(TEXT(""))
		, Val(0)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString Key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	int32 Val;
	//TArray<T> Value;
};


USTRUCT(BlueprintType)
struct FST_Modifier
{
	GENERATED_USTRUCT_BODY()
public:
	FST_Modifier()
		: Id(TEXT(""))
		, Description(TEXT(""))
		, Amount(0)
		, TurnsLeft(-1)
		, Stats(TArray<FST_Stat>())
	{}
	TMap<FString, int32> Needs;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	int32 TurnsLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	TArray<FST_Stat> Stats;
};


USTRUCT(BlueprintType)
struct FST_StatState
{
	GENERATED_USTRUCT_BODY()
public:
	FST_StatState()
		: Confidence(EStatStates::Normal)
		, Endurance(EStatStates::Normal)
		, Cognitive(EStatStates::Normal)
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EStatStates Confidence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EStatStates Endurance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EStatStates Cognitive;
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