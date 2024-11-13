// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTickBoxHorizontalBox.h"
#include "GFormTickBox.h"

void UGFormTickBoxHorizontalBox::OnWidgetRebuilt()
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
			CastedChild->OnTickBoxChecked.AddUniqueDynamic(this, &UGFormTickBoxHorizontalBox::OnTickBoxSelected);
		}
	}
}

void UGFormTickBoxHorizontalBox::OnTickBoxSelected(UGFormTickBox* NewSelection, bool Choice)
{
	//If we want to add but there is no data within the first slot which will always exist
	if (Choice && WidgetData->GetEntryData(0).EntryData.IsEmpty())
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
		WidgetData->RemoveEntryData(RowEntryID, NewSelection->WidgetData->GetEntryData(0).EntryData);
}

TArray<FGFormInformation> UGFormTickBoxHorizontalBox::GetFormDetails()
{
	return WidgetData->EntryData;
}
