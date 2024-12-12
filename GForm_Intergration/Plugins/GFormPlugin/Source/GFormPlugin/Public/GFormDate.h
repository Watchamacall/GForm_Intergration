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
class GFORMPLUGIN_API UGFormDate : public UHorizontalBox, public IGFormInterface
{
	GENERATED_BODY()
	
public:
    UGFormDate();

public:
    /*
    * The Styling for the Time TextBoxes
    */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GForm")
    FEditableTextStyle DateStyle;

protected:
    /*
    * The Data Component which holds all information about the Form Instance
    */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
    UGFormDataComponent* WidgetData;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "GForm")
    UVerticalBox* DayVerticalBox;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "GForm")
    UVerticalBox* MonthVerticalBox;
    
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "GForm")
    UVerticalBox* YearVerticalBox;

    /** Day Text Box */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "GForm")
    UEditableText* DayTextBox;

    /**  Month Text Box. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "GForm")
    UEditableText* MonthTextBox;
    
    /**  Year Text Box. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "GForm")
    UEditableText* YearTextBox;

    UPROPERTY()
    UTextBlock* DayToMonthDashTextBlock;
    
    UPROPERTY()
    UTextBlock* MonthToYearDashTextBlock;
public:
#if WITH_EDITOR
    virtual const FText GetPaletteCategory() override
    {
        return NSLOCTEXT("UMG", "GFormCategory", "GForm");
    }
#endif
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;

    /*
    * 
    */
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

    virtual TArray<FGFormInformation> GetFormDetails() override;
};
