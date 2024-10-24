// Fill out your copyright notice in the Description page of Project Settings.

//Change this value if GForms changes the Maximum value that the Linear Scale can go to
#define LINEAR_SCALE_MAX 10
#define RATING_SCALE_MAX 9

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/ActorComponent.h"
#include "GFormWidgetSecondaryClass.generated.h"

class UGFormInterface;

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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFORM_INTERGRATION_API UGFormDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    /*
    * A link of EntryID alongside the data to send
    */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GForm|Entry")
    TArray<FGFormInformation> EntryData;

    /*
    * Adds an instance of the inputted EntryID and the EnteredData
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    void AddEntryData(const FString& InEntryID, const FString& InEnteredData) { 
        EntryData.Add(FGFormInformation(InEntryID, InEnteredData)); 
    }

    /*
    * Removes an instance of the inputted EntryID and the EnteredData
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    void RemoveEntryData(const FString& InEntryID, const FString& InEnteredData)
    {
        for (size_t i = 0; i < EntryData.Num(); i++)
        {
            auto Data = EntryData[i];
            if (Data.EntryID == InEntryID && Data.EntryData == InEnteredData)
            {
                EntryData.RemoveAt(i);
                break;
            }
        }
    }

    /*
    * Replaces the element at Index with the inputted InEnteredData
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    void ReplaceEnteredData(const int Index, const FString& InEnteredData) {
        if (EntryData.Num() < Index)
        {
            EntryData.SetNum(Index+1);
        }
        EntryData[Index].EntryData = InEnteredData;
    }

    /*
    * Replaces the entire EntryData of Index with the given EntryID and the EnteredData
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    void ReplaceEntryData(const int Index, const FString& InEntryID, const FString& InEnteredData) {
        EntryData[Index] = FGFormInformation(InEntryID, InEnteredData);
    }

    /*
    * Returns the FGFormInformation Data which is held in Index, if valid else returns empty FGFormInformation
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    FGFormInformation GetEntryData (int Index) const {
        if (EntryData.IsValidIndex(Index))
        {
            return EntryData[Index];
        }
        return FGFormInformation();
    }

    /*
    * Returns true if EntryData is valid in given Index Slot
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    bool EntryDataExistsIndex(int Index) {
        return EntryData.IsValidIndex(Index);
    }

    /*
    * Returns true if InEntryID is found inside EntryData
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    bool EntryDataFromEntryID(const FString& InEntryID) {
        for (auto Data : EntryData)
        {
            if (Data.EntryData == InEntryID)
            {
                return true;
            }
        }
        return false;
    }

    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    int NumOfEntryData() {
        return EntryData.Num();
    }
};
