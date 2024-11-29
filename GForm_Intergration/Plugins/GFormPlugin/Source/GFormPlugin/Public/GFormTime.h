// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include "Components/EditableText.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "GFormTime.generated.h"

/**
 * 
 */
UCLASS()
class GFORMPLUGIN_API UGFormTime : public UHorizontalBox, public IGFormInterface
{
    GENERATED_BODY()

public:

    UGFormTime();

    /*
    * Returns what the hour is currently set to
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Time")
    FText GetHour() const;

    /*
    * Returns what the minute is currently set to
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Time")
    FText GetMinute() const;

    /*
    * Returns true if the Hour has been set correctly
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Time")
    bool SetHour(const int32 NewTime);

    /*
    * Returns true if the Minute has been set correctly
    */
    UFUNCTION(BlueprintCallable, Category = "GForm|Time")
    bool SetMinute(const int32 NewTime);

#if WITH_EDITOR
    virtual const FText GetPaletteCategory() override
    {
        return NSLOCTEXT("UMG", "GFormCategory", "GForm");
    }
#endif

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

    virtual void SynchronizeProperties() override;

    virtual TArray<FGFormInformation> GetFormDetails();

private:

    /*
    * Checks over the inputted text and ensures it is valid for the Hour time, including whether the text contains alphabetical characters and the maximum integer it will allow
    */
    UFUNCTION()
    void HourTextCheck(const FText& Text);

    /*
    * Checks over the inputted text and ensures it is valid for the Minute time, including whether the text contains alphabetical characters and the maximum integer it will allow
    */
    UFUNCTION()
    void MinuteTextCheck(const FText& Text);

    /*
    * Sets the WidgetData EntryData in the correct format
    */
    void SetWidgetTime();

public:
    /*
    * The Styling for the Time TextBoxes
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GForm")
    FEditableTextStyle TimeStyle;

protected:
    /*
    * The Data Component which holds all information about the Form Instance
    */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
    UGFormDataComponent* WidgetData;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UVerticalBox* HourVerticalBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UVerticalBox* MinuteVerticalBox;

    /** Hour Text Box */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UEditableText* HourTextBox;

    UPROPERTY()
    UTextBlock* ColonTextBlock;

    /**  Minute Text Box. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UEditableText* MinuteTextBox;
};
