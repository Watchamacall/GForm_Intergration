// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormDate.h"
#include "Kismet/KismetMathLibrary.h"

TSharedRef<SWidget> UGFormDate::RebuildWidget()
{
    if (!WidgetData)
        WidgetData = NewObject<UGFormDataComponent>(this);

	TSharedRef<SWidget> ParentRef = Super::RebuildWidget();

	ClearChildren();

    /*
    * Creating the Vertical Boxes
    */
    DayVerticalBox = NewObject<UVerticalBox>(this, FName("Day Vertical Box"));
    if (!DayVerticalBox)
    {
        return ParentRef;
    }
    MonthVerticalBox = NewObject<UVerticalBox>(this, FName("Month Vertical Box"));
    if (!MonthVerticalBox)
    {
        return ParentRef;
    }
    YearVerticalBox = NewObject<UVerticalBox>(this, FName("Year Vertical Box"));
    if (!YearVerticalBox)
    {
        return ParentRef;
    }

    /*
    * Creating the Dash TextBlocks
    */
    DayToMonthDashTextBlock = NewObject<UTextBlock>(this, FName("Day-Month Dash TextBlock"));
    if (DayToMonthDashTextBlock)
    {
        DayToMonthDashTextBlock->SetText(FText::FromString("-"));
    }
    MonthToYearDashTextBlock = NewObject<UTextBlock>(this, FName("Month-Year Dash TextBlock"));
    if (MonthToYearDashTextBlock)
    {
        MonthToYearDashTextBlock->SetText(FText::FromString("-"));
    }

    //auto Date = UKismetMathLibrary::Now();

    /*
    * Creating the EditableTextBoxes
    */
    DayTextBox = NewObject<UEditableText>(this, FName("Day"));
    if (DayTextBox)
    {
        // Add HourTextBox to the HourVerticalBox
        UVerticalBoxSlot* HourSlot = DayVerticalBox->AddChildToVerticalBox(DayTextBox);
        DayTextBox->SetText(FText::FromString("01"));
        DayTextBox->SetHintText(FText::FromString("01"));
        DayTextBox->OnTextChanged.AddUniqueDynamic(this, &UGFormDate::DayTextCheck);
        DayTextBox->OnTextCommitted.AddUniqueDynamic(this, &UGFormDate::DayCommittedCheck);
    }

    MonthTextBox = NewObject<UEditableText>(this, FName("Month"));
    if (MonthTextBox)
    {
        // Add MinuteTextBox to the MinuteVerticalBox
        UVerticalBoxSlot* MinuteSlot = MonthVerticalBox->AddChildToVerticalBox(MonthTextBox);
        MonthTextBox->SetText(FText::FromString("01"));
        MonthTextBox->SetHintText(FText::FromString("01"));
        MonthTextBox->OnTextChanged.AddUniqueDynamic(this, &UGFormDate::MonthTextCheck);
        MonthTextBox->OnTextCommitted.AddUniqueDynamic(this, &UGFormDate::MonthCommittedCheck);
    }

    YearTextBox = NewObject<UEditableText>(this, FName("Year"));
    if (YearTextBox)
    {
        // Add YearTextBox to the YearVerticalBox
        UVerticalBoxSlot* YearSlot = YearVerticalBox->AddChildToVerticalBox(YearTextBox);
        YearTextBox->SetText(FText::FromString("2000"));
        YearTextBox->SetHintText(FText::FromString("2000"));
        YearTextBox->OnTextChanged.AddUniqueDynamic(this, &UGFormDate::YearTextCheck);
        YearTextBox->OnTextCommitted.AddUniqueDynamic(this, &UGFormDate::YearCommittedCheck);
    }

    // Create a custom horizontal box layout combining the parent widget
    TSharedRef<SHorizontalBox> CustomHorizontalBox = SNew(SHorizontalBox)
        + SHorizontalBox::Slot()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        .AutoWidth()
        [
            DayVerticalBox->TakeWidget() // Convert the UVerticalBox to an SWidget
        ]
        + SHorizontalBox::Slot()
        .AutoWidth()
        .Padding(1.f, 0.f, 0.f, 0.f)
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            DayToMonthDashTextBlock->TakeWidget() // Convert the UTextBlock to an SWidget
        ]
        + SHorizontalBox::Slot()
        .AutoWidth()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            MonthVerticalBox->TakeWidget() // Convert the UVerticalBox to an SWidget
        ]
        + SHorizontalBox::Slot()
        .Padding(1.f, 0.f, 0.f, 0.f)
        .AutoWidth()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            MonthToYearDashTextBlock->TakeWidget() // Convert the UVerticalBox to an SWidget
        ] 
        + SHorizontalBox::Slot()
        .AutoWidth()
        .HAlign(HAlign_Center)
        .VAlign(VAlign_Center)
        [
            YearVerticalBox->TakeWidget() // Convert the UVerticalBox to an SWidget
        ];

    // Wrap the parent widget inside the custom widget
    return SNew(SOverlay)
        + SOverlay::Slot()
        [
            ParentRef // Keep the parent layout
        ]
        + SOverlay::Slot()
        [
            CustomHorizontalBox // Add the custom layout
        ];
}

void UGFormDate::DayTextCheck(const FText& Text)
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

    if (IntValue > DAY_MAX)
    {
        ConvertedString = FString::FromInt(DAY_MAX);
    }
    DayTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetDate();
}

void UGFormDate::MonthTextCheck(const FText& Text)
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

    if (IntValue > MONTH_MAX)
    {
        ConvertedString = FString::FromInt(MONTH_MAX);
    }
    MonthTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetDate();
}

void UGFormDate::YearTextCheck(const FText& Text)
{
    FString ConvertedString = Text.ToString();

    if (ConvertedString.Len() > 0)
    {
        if (FChar::IsAlpha(ConvertedString[ConvertedString.Len() - 1]))
        {
            ConvertedString.RemoveAt(ConvertedString.Len() - 1);
        }
        if (ConvertedString.Len() > YEAR_MAX_CHAR)
        {
            ConvertedString = ConvertedString.Left(YEAR_MAX_CHAR);
        }
    }
    int IntValue = FCString::Atoi(*ConvertedString);

    if (IntValue > YEAR_MAX)
    {
        ConvertedString = FString::FromInt(YEAR_MAX);
    }
    YearTextBox->SetText(FText::FromString(ConvertedString));
    SetWidgetDate();
}

void UGFormDate::DayCommittedCheck(const FText& Text, ETextCommit::Type CommitMethod)
{
    FString ConvertedString = Text.ToString();

    if (FCString::Atoi(*ConvertedString) <= 0)
    {
        ConvertedString = "1";
    }

    int MonthInInt = FCString::Atoi(*MonthTextBox->GetText().ToString());
    
    //EVEN MONTH
    if (MonthInInt % 2 == 0)
    {
        //Is before August and Day chosen is 31
        if (MonthInInt < 8 && ConvertedString == "31")
        {
            ConvertedString = "30";
        }
        //Feburary Shenanagins
        else if (MonthInInt == 2)
        {
            int YearLoaded = FCString::Atoi(*YearTextBox->GetText().ToString());
            //For Leap Year: Must divide by 4, cannot be divided by 100 unless is divisible by 400
            if (YearLoaded % 4 == 0 && (YearLoaded % 100 != 0 || YearLoaded % 400 == 0))
            {
                //Day chosen is above the Leap Year
                if (FCString::Atoi(*ConvertedString) > 29)
                {
                    ConvertedString = "29";
                }
            }
            //Not a leap year
            else
            {
                //Day chosen is above non leap year Feb
                if (FCString::Atoi(*ConvertedString) > 28)
                {
                    ConvertedString = "28";
                }
            }
        }
    }
    //Odd Month
    else
    {
        //If Month is above June and the Day chosen is 31
        if (MonthInInt > 7 && ConvertedString == "31")
        {
            ConvertedString = "30";
        }
    }
    //TODO: Add a check to ensure the month works with the day that they enter. If Feburary, check the leap year status and make sure they can only enter 28 otherwise 
    /*
    * Jan - 31
    * Feb - 28/29
    * Mar - 31
    * Apr - 30
    * May - 31
    * Jun - 30
    * Jul - 31
    * Aug - 31
    * Sept - 30
    * Oct - 31
    * Nov - 30
    * Dec - 31
    */

    /*
    * LEAP YEAR CONDITIONS:
    * MUST BE DIVISIBLE BY 4
    * CANNOT BE DIVISIBLE BY 100
    * UNLESS DIVISIBLE BY 400
    * 
    * WHEN A LEAP YEAR OCCURS, FEBURARY HAS 29 DAYS
    * IF IT IS NOT A LEAP YEAR THEN THERE ARE ONLY 28 DAYS
    */

    DayTextBox->SetText(FText::FromString(ConvertedString));
}

void UGFormDate::MonthCommittedCheck(const FText& Text, ETextCommit::Type CommitMethod)
{
    FString ConvertedString = Text.ToString();

    if (FCString::Atoi(*ConvertedString) <= 0)
    {
        ConvertedString = "1";
    }

    MonthTextBox->SetText(FText::FromString(ConvertedString));
}

void UGFormDate::YearCommittedCheck(const FText& Text, ETextCommit::Type CommitMethod)
{
    FString ConvertedString = Text.ToString();

    if (FCString::Atoi(*ConvertedString) <= 0)
    {
        ConvertedString = "1";
    }
    if (ConvertedString.Len() < YEAR_MAX_CHAR)
    {
        while (ConvertedString.Len() != YEAR_MAX_CHAR)
        {
            ConvertedString.AppendChar('0');
        }
    }
    YearTextBox->SetText(FText::FromString(ConvertedString));
}

void UGFormDate::SetWidgetDate()
{
    WidgetData->ReplaceEnteredData(0, *FString(DayTextBox->GetText().ToString() + '-' + MonthTextBox->GetText().ToString() + '-' + YearTextBox->GetText().ToString()));

}
