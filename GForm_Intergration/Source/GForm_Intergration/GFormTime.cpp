// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTime.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"

UGFormTime::UGFormTime()
{
    HourTextBox = nullptr;
    MinuteTextBox = nullptr;
}

TSharedRef<SWidget> UGFormTime::RebuildWidget()
{
    if (!WidgetData)
        WidgetData = NewObject<UGFormDataComponent>(this);

    // Call the parent class's RebuildWidget() to construct the base SWidget
    TSharedRef<SWidget> ParentWidget = Super::RebuildWidget();

    // Clear existing children to avoid duplication
    ClearChildren();

    /*
    * Creating the Vertical Boxes
    */
    HourVerticalBox = NewObject<UVerticalBox>(this, FName("Hour VertBox"));
    if (!HourVerticalBox)
    {
        return ParentWidget;
    }
    MinuteVerticalBox = NewObject<UVerticalBox>(this, FName("Minute VertBox"));
    if (!MinuteVerticalBox)
    {
        return ParentWidget;
    }

    /*
    * Creating the TextBox for the Colon
    */
    ColonTextBlock = NewObject<UTextBlock>(this, FName("Colon Text"));
    if (ColonTextBlock)
    {
        ColonTextBlock->SetText(FText::FromString(":")); // Set default text for the colon
    }

    /*
    * Creating the EditableTextBoxes
    */
    HourTextBox = NewObject<UEditableText>(this, FName("Hour"));
    if (HourTextBox)
    {
        // Add HourTextBox to the HourVerticalBox
        UVerticalBoxSlot* HourSlot = HourVerticalBox->AddChildToVerticalBox(HourTextBox);
        HourTextBox->SetText(FText::FromString("00"));
        HourTextBox->SetHintText(FText::FromString("00"));
        HourTextBox->OnTextChanged.AddUniqueDynamic(this, &UGFormTime::HourTextCheck);
    }

    MinuteTextBox = NewObject<UEditableText>(this, FName("Minute"));
    if (MinuteTextBox)
    {
        // Add MinuteTextBox to the MinuteVerticalBox
        UVerticalBoxSlot* MinuteSlot = MinuteVerticalBox->AddChildToVerticalBox(MinuteTextBox);
        MinuteTextBox->SetText(FText::FromString("00"));
        MinuteTextBox->SetHintText(FText::FromString("00"));
        MinuteTextBox->OnTextChanged.AddUniqueDynamic(this, &UGFormTime::MinuteTextCheck);
    }

    // Create a custom horizontal box layout combining the parent widget
    TSharedRef<SHorizontalBox> CustomHorizontalBox = SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        .AutoWidth()
        [
            HourVerticalBox->TakeWidget() // Convert the UVerticalBox to an SWidget
        ]
        + SHorizontalBox::Slot()
        .AutoWidth()
        .Padding(1.f,0.f,0.f,0.f)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            ColonTextBlock->TakeWidget() // Convert the UTextBlock to an SWidget
        ]
        + SHorizontalBox::Slot()
        .AutoWidth()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            MinuteVerticalBox->TakeWidget() // Convert the UVerticalBox to an SWidget
        ];

    // Wrap the parent widget inside the custom widget
    return SNew(SOverlay)
        + SOverlay::Slot()
        [
            ParentWidget // Keep the parent layout
        ]
        + SOverlay::Slot()
        [
            CustomHorizontalBox // Add the custom layout
        ];
}

TArray<FGFormInformation> UGFormTime::GetFormDetails()
{
    return WidgetData->EntryData;
}

void UGFormTime::HourTextCheck(const FText& Text)
{
    FString ConvertedString = Text.ToString();

    if (ConvertedString.Len() > 0)
    {
        if (FChar::IsAlpha(ConvertedString[ConvertedString.Len() - 1]))
        {
            ConvertedString.RemoveAt(ConvertedString.Len() - 1);
        }
        if (ConvertedString.Len() > TIME_MAX_CHAR)
        {
            ConvertedString = ConvertedString.Left(TIME_MAX_CHAR);
        }
    }
    int IntValue = FCString::Atoi(*ConvertedString);
    
    if (IntValue > HOUR_TIME_MAX)
    {
        ConvertedString = FString::FromInt(HOUR_TIME_MAX);
    }
    HourTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetTime();
}

void UGFormTime::MinuteTextCheck(const FText& Text)
{
    FString ConvertedString = Text.ToString();

    if (ConvertedString.Len() > 0)
    {
        if (FChar::IsAlpha(ConvertedString[ConvertedString.Len() - 1]))
        {
            ConvertedString.RemoveAt(ConvertedString.Len() - 1);
        }
        if (ConvertedString.Len() > TIME_MAX_CHAR)
        {
            ConvertedString = ConvertedString.Left(TIME_MAX_CHAR);
        }
    }
    int IntValue = FCString::Atoi(*ConvertedString);

    if (IntValue > MINUTE_TIME_MAX)
    {
        ConvertedString = FString::FromInt(MINUTE_TIME_MAX);
    }
    MinuteTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetTime();
}

void UGFormTime::SetWidgetTime()
{
    WidgetData->ReplaceEnteredData(0, *FString(HourTextBox->GetText().ToString() + ':' + MinuteTextBox->GetText().ToString()));
}
