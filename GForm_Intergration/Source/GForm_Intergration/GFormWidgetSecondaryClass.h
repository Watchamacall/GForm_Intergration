// Fill out your copyright notice in the Description page of Project Settings.

//Change this value if GForms changes the Maximum value that the Linear Scale can go to
#define LINEAR_SCALE_MAX 10
#define RATING_SCALE_MAX 9

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "GFormInterface.h"
#include "Components/ActorComponent.h"
#include "GFormInterface.h"
#include "GFormWidgetSecondaryClass.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GFORM_INTERGRATION_API UGFormDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    /*
    * The Text which holds the Data which will be transmitted
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GForm|Data")
    TArray<FString> EnteredData;

    /*
    * The Entry ID used in the URL to send the data
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GForm|Entry")
    TArray<FString> EntryID;

    /*
    * A link of EntryID alongside the data to send
    */
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GForm|Entry")
    TArray<FGFormInformation> EntryData;

    /*
    * Adds an instance of the inputted EntryID and the EnteredData
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    void AddEntryData(const FString& InEntryID, const FString& InEnteredData) { EntryData.Add(FGFormInformation(InEntryID, InEnteredData)); }

    /*
    * Removes an instance of the inputted EntryID and the EnteredData
    */
    UFUNCTION(BlueprintCallable, EditAnywhere, Category = "GForm|Entry")
    void RemoveEntryData(const FString& InEntryID, const FString& InEnteredData)
    {
        for (auto Data : EntryData)
        {
            if (Data.EntryID == InEntryID && Data.EntryData == InEnteredData)
            {
                EntryData.Remove(Data);
                break;
            }
        }
    }

    /*
    * Returns the EntryID
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    FString GetEntryID() const { return EntryID; }

    UFUNCTION(BlueprintCallable, Category = "GForm|Data")
    void AddEnteredData(FText Data) { EnteredData.Add(Data.ToString()); }

    UFUNCTION(BlueprintCallable, Category = "GForm|Data")
    void RemoveEnteredData(FText DataToRemove) { EnteredData.Remove(DataToRemove.ToString()); }

    UFUNCTION(BlueprintCallable, Category = "GForm|Data")
    TArray<FString> GetAllEnteredData() const { return EnteredData; }
};
