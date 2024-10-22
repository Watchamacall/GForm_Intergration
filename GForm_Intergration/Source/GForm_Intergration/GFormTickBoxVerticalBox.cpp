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
	Choice ? WidgetData->AddEnteredData(FText::FromString(NewSelection->WidgetData->GetAllEnteredData()[0])) : WidgetData->RemoveEnteredData(FText::FromString(NewSelection->WidgetData->GetAllEnteredData()[0]));
}

TArray<FGFormInformation> UGFormTickBoxVerticalBox::GetFormDetails()
{
	TArray<FGFormInformation> ReturnArray;

	/*
	* For each Box that is ticked add it's:
	*	Entry ID for the TickBox
	*	Data from the TickBox
	*/
	for (auto TickedBox : TickedBoxes)
	{
		ReturnArray.Add(FGFormInformation(TickedBox->WidgetData->GetEntryID(), TickedBox->WidgetData->GetAllEnteredData()[0]));
	}

	return ReturnArray;
}