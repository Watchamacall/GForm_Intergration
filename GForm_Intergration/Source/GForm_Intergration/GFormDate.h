// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include <Components/TextBlock.h>
#include <Components/VerticalBox.h>
#include "Components/EditableText.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "GFormDate.generated.h"

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormDate : public UHorizontalBox
{
	GENERATED_BODY()
	
protected:
    /*
    * The Data Component which holds all information about the Form Instance
    */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
    UGFormDataComponent* WidgetData;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UVerticalBox* DayVerticalBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UVerticalBox* MonthVerticalBox;
    
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UVerticalBox* YearVerticalBox;

    /** Day Text Box */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UEditableText* DayTextBox;

    /**  Month Text Box. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UEditableText* MonthTextBox;
    
    /**  Year Text Box. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UEditableText* YearTextBox;

    UPROPERTY()
    UTextBlock* DayToMonthDashTextBlock;
    
    UPROPERTY()
    UTextBlock* MonthToYearDashTextBlock;

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

    UFUNCTION()
    void DayTextCheck(const FText& Text);

    UFUNCTION()
    void MonthTextCheck(const FText& Text);

    UFUNCTION()
    void YearTextCheck(const FText& Text);

    UFUNCTION()
    void DayCommittedCheck(const FText& Text, ETextCommit::Type CommitMethod);
    
    UFUNCTION()
    void MonthCommittedCheck(const FText& Text, ETextCommit::Type CommitMethod);
    
    UFUNCTION()
    void YearCommittedCheck(const FText& Text, ETextCommit::Type CommitMethod);

    void SetWidgetDate();
};
