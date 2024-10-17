// Fill out your copyright notice in the Description page of Project Settings.

//Change this value if GForms changes the Maximum value that the Linear Scale can go to
#define LINEAR_SCALE_MAX 10
#define RATING_SCALE_MAX 9

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/ActorComponent.h"
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
    FString EnteredData;

    /*
    * The Entry ID used in the URL to send the data
    */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GForm|Entry")
    FString EntryID;

    /*
    * Returns the EntryID
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Entry")
    FString GetEntryID() const { return EntryID; }

    UFUNCTION(BlueprintCallable, Category = "GForm|Data")
    void SetEnteredData(FText Data) { EnteredData = Data.ToString(); }

    UFUNCTION(BlueprintCallable, Category = "GForm|Data")
    FText GetEnteredData() const { return FText::FromString(EnteredData); }
};
