// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTickBoxLogic.h"
#include "GFormWidgetSecondaryClass.h"
#include "Components/PanelWidget.h"
#include "GFormTickBox.h"
#include "GFormTickBoxVerticalBox.h"
#include "GFormTickBoxHorizontalBox.h"

void FGFormTickBoxLogic::InitialiseComponent(UGFormDataComponent*& WidgetData, UPanelWidget* Panel)
{
    if (!WidgetData)
        WidgetData = NewObject<UGFormDataComponent>(Panel);

    TArray<UWidget*> Children = Panel->GetAllChildren();
    for (UWidget* Child : Children)
    {
        if (UGFormTickBox* TickBox = Cast<UGFormTickBox>(Child))
        {
            if (UGFormTickBoxVerticalBox* VerticalBox = Cast<UGFormTickBoxVerticalBox>(Panel))
            {
                // Bind the delegate to the specific panel instance
                TickBox->OnTickBoxChecked.AddUniqueDynamic(VerticalBox, &UGFormTickBoxVerticalBox::OnTickBoxSelected);
            }
            else if (UGFormTickBoxHorizontalBox* HorizontalBox = Cast<UGFormTickBoxHorizontalBox>(Panel))
            {
                TickBox->OnTickBoxChecked.AddUniqueDynamic(HorizontalBox, &UGFormTickBoxHorizontalBox::OnTickBoxSelected);
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("One or more objects use TickBoxLogic when it is not valid for this "));
            }
        }
    }
}

void FGFormTickBoxLogic::HandleSelectedTickBox(UGFormDataComponent* WidgetData, UGFormTickBox* SelectedTickBox, bool Choice)
{
    //If we want to add but there is no data within the first slot which will always exist
    if (Choice && WidgetData->GetEntryData(0).EntryData.IsEmpty())
    {
        WidgetData->ReplaceEnteredData(0, SelectedTickBox->WidgetData->GetEntryData(0).EntryData);
        return;
    }
    //If we remove but only have one element in the list
    else if (!Choice && WidgetData->NumOfEntryData() == 1)
    {
        WidgetData->ReplaceEnteredData(0, "");
        return;
    }

    //We have more than two elements in the array so do below

    FString RowEntryID = WidgetData->GetEntryData(0).EntryID;

    Choice ?
        WidgetData->AddEntryData(RowEntryID, SelectedTickBox->WidgetData->GetEntryData(0).EntryData) :
        WidgetData->RemoveEntryData(RowEntryID, SelectedTickBox->WidgetData->GetEntryData(0).EntryData);
}
