// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormMultipleChoiceLogic.h"
#include "GFormMultipleChoiceVerticalBox.h"
#include "GFormMultipleChoiceHorizontalBox.h"

void FGFormMultipleChoiceLogic::InitialiseComponent(UGFormDataComponent*& WidgetData, UPanelWidget* Panel, TArray<UGFormMultipleChoiceBox*>& KnownBoxes)
{
	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(Panel);

	KnownBoxes.Empty();

	TArray<UWidget*> Children = Panel->GetAllChildren();

	for (size_t i = 0; i < Children.Num(); i++)
	{
		if (UGFormMultipleChoiceBox* CastedChild = Cast<UGFormMultipleChoiceBox>(Children[i]))
		{
			if (UGFormMultipleChoiceVerticalBox* VerticalBox = Cast<UGFormMultipleChoiceVerticalBox>(Panel))
			{
				// Bind the delegate to the specific panel instance
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(VerticalBox, &UGFormMultipleChoiceVerticalBox::OnCheckBoxSelected);
			}
			else if (UGFormMultipleChoiceHorizontalBox* HorizontalBox = Cast<UGFormMultipleChoiceHorizontalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(HorizontalBox, &UGFormMultipleChoiceHorizontalBox::OnCheckBoxSelected);
			}

			KnownBoxes.Add(CastedChild);
		}
	}
}

void FGFormMultipleChoiceLogic::HandleSelectedMultipleChoiceBox(UGFormDataComponent* WidgetData, UGFormMultipleChoiceBox* SelectedMultipleChoiceBox, bool Choice, TArray<UGFormMultipleChoiceBox*>& KnownBoxes)
{
	for (UGFormMultipleChoiceBox* Box : KnownBoxes)
	{
		if (Box == SelectedMultipleChoiceBox)
		{
			WidgetData->ReplaceEnteredData(0, *Box->WidgetData->GetEntryData(0).EntryData);

			if (!Choice)
			{
				Box->SetCheckedState(ECheckBoxState::Checked);
			}
		}
		else if (Box->GetCheckedState() == ECheckBoxState::Checked)
		{
			Box->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}