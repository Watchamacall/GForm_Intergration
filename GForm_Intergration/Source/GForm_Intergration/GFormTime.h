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
class GFORM_INTERGRATION_API UGFormTime : public UHorizontalBox, public IGFormInterface
{
    GENERATED_BODY()

public:

    UGFormTime();

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

    virtual TArray<FGFormInformation> GetFormDetails();

private:

    UFUNCTION()
    void HourTextCheck(const FText& Text);

    UFUNCTION()
    void MinuteTextCheck(const FText& Text);

    void SetWidgetTime();

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
