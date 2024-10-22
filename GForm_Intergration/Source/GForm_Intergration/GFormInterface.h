// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GFormInterface.generated.h"

USTRUCT(BlueprintType)
struct FGFormInformation
{
    GENERATED_BODY()

    // The unique identifier for the form entry
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GForm")
    FString EntryID;

    // The data associated with the form entry
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GForm")
    FString EntryData;

    // Default constructor
    FGFormInformation()
        : EntryID(TEXT("")), EntryData(TEXT("")) {}

    // Parameterized constructor
    FGFormInformation(const FString& InEntryID, const FString& InEntryData)
        : EntryID(InEntryID), EntryData(InEntryData) {}
};

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UGFormInterface : public UInterface
{
	GENERATED_BODY()	
};

class GFORM_INTERGRATION_API IGFormInterface
{
	GENERATED_BODY()
public:
    /*
    * Implementation of getting the Form Details in the format of the FGFormInformation Struct
    */
	virtual TArray<FGFormInformation> GetFormDetails();
};
