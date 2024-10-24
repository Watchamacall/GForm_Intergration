// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTickBoxVerticalBox.h"
#include "GFormTickBox.h"

void UGFormTickBoxVerticalBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);

	TArray<UWidget*> Children = GetAllChildren();

	for (size_t i = 0; i < Children.Num(); i++)
	{
		if (UGFormTickBox* CastedChild = Cast<UGFormTickBox>(Children[i]))
		{
			//Add the functionality for when a Multiple Choice Box is selected
			CastedChild->OnTickBoxChecked.AddUniqueDynamic(this, &UGFormTickBoxVerticalBox::OnTickBoxSelected);
		}
	}
}

void UGFormTickBoxVerticalBox::OnTickBoxSelected(UGFormTickBox* NewSelection, bool Choice)
{
	//If we add but we only have one element in the list
	if (Choice && WidgetData->NumOfEntryData() == 1)
	{
		WidgetData->ReplaceEnteredData(0, NewSelection->WidgetData->GetEntryData(0).EntryData);
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
		WidgetData->AddEntryData(RowEntryID, NewSelection->WidgetData->GetEntryData(0).EntryData) :
		WidgetData->AddEntryData(RowEntryID, NewSelection->WidgetData->GetEntryData(0).EntryData);
}

TArray<FGFormInformation> UGFormTickBoxVerticalBox::GetFormDetails()
{
	TArray<FGFormInformation> ReturnArray;

	/*
	* For each Box that is ticked add it's:
	*	Entry ID for the TickBox
	*	Data from the TickBox
	*/
	//for (auto TickedBox : TickedBoxes)
	//{
	//	ReturnArray.Add(FGFormInformation(TickedBox->WidgetData->GetEntryID(), TickedBox->WidgetData->GetAllEnteredData()[0]));
	//}

	return ReturnArray;
}