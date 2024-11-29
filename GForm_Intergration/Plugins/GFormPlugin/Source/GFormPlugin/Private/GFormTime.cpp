// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTime.h"
#include "Components/HorizontalBoxSlot.h"
#include "Styling/UMGCoreStyle.h"
#include "Components/VerticalBoxSlot.h"
#include "Engine/Font.h"

UGFormTime::UGFormTime()
{
    HourTextBox = nullptr;
    MinuteTextBox = nullptr;

    //Load Default Unreal Font
    static ConstructorHelpers::FObjectFinder<UFont> FontAsset(TEXT("Font'/Engine/EngineFonts/Roboto.Roboto'"));

    if (FontAsset.Succeeded())
    {
        TimeStyle.SetFont(FSlateFontInfo(FontAsset.Object, 24));
    }

    
}

FText UGFormTime::GetHour() const
{
    return HourTextBox->GetText();
}

FText UGFormTime::GetMinute() const
{
    return MinuteTextBox->GetText();
}

bool UGFormTime::SetHour(const int32 NewTime)
{
    HourTextCheck(FText::AsNumber(NewTime));

    return HourTextBox->GetText().ToString() == FString::FromInt(NewTime);
}

bool UGFormTime::SetMinute(const int32 NewTime)
{
    MinuteTextCheck(FText::AsNumber(NewTime));

    return MinuteTextBox->GetText().ToString() == FString::FromInt(NewTime);
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
        ColonTextBlock->SetColorAndOpacity(TimeStyle.ColorAndOpacity);
        ColonTextBlock->SetFont(TimeStyle.Font);
        ColonTextBlock->SetStrikeBrush(TimeStyle.BackgroundImageComposing);

        ColonTextBlock->SetText(FText::FromString(":")); // Set default text for the colon
    }

    /*
    * Creating the EditableTextBoxes
    */
    HourTextBox = NewObject<UEditableText>(this, FName("Hour"));
    if (HourTextBox)
    {
        HourTextBox->WidgetStyle = TimeStyle;
        // Add HourTextBox to the HourVerticalBox
        UVerticalBoxSlot* HourSlot = HourVerticalBox->AddChildToVerticalBox(HourTextBox);
        HourTextBox->SetText(FText::FromString("00"));
        HourTextBox->SetHintText(FText::FromString("00"));
        HourTextBox->OnTextChanged.AddUniqueDynamic(this, &UGFormTime::HourTextCheck);
    }

    MinuteTextBox = NewObject<UEditableText>(this, FName("Minute"));
    if (MinuteTextBox)
    {
        MinuteTextBox->WidgetStyle = TimeStyle;
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

void UGFormTime::SynchronizeProperties()
{
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
        //Restrict to Numerical Values only
        if (FChar::IsAlpha(ConvertedString[ConvertedString.Len() - 1]))
        {
            ConvertedString.RemoveAt(ConvertedString.Len() - 1);
        }
        //Limit Text to TIME_MAX_CHAR
        if (ConvertedString.Len() > TIME_MAX_CHAR)
        {
            ConvertedString = ConvertedString.Left(TIME_MAX_CHAR);
        }
    }
    int IntValue = FCString::Atoi(*ConvertedString);
    
    //Clamp Hour to HOUR_TIME_MAX
    ConvertedString = FString::FromInt(FMath::Clamp(IntValue, 0, HOUR_TIME_MAX));

    HourTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetTime();
}

void UGFormTime::MinuteTextCheck(const FText& Text)
{
    FString ConvertedString = Text.ToString();

    if (ConvertedString.Len() > 0)
    {
        //Restrict String to Numerical Values
        if (FChar::IsAlpha(ConvertedString[ConvertedString.Len() - 1]))
        {
            ConvertedString.RemoveAt(ConvertedString.Len() - 1);
        }
        //Limit String to TIME_MAX_CHAR
        if (ConvertedString.Len() > TIME_MAX_CHAR)
        {
            ConvertedString = ConvertedString.Left(TIME_MAX_CHAR);
        }
    }
    int IntValue = FCString::Atoi(*ConvertedString);

    //Clamp String to MINUTE_TIME_MAX
    ConvertedString = FString::FromInt(FMath::Clamp(IntValue, 0, MINUTE_TIME_MAX));

    MinuteTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetTime();
}

void UGFormTime::SetWidgetTime()
{
    WidgetData->ReplaceEnteredData(0, *FString(HourTextBox->GetText().ToString() + ':' + MinuteTextBox->GetText().ToString()));
}
