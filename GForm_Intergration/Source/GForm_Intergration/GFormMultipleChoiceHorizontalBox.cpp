// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormMultipleChoiceHorizontalBox.h"
#include "GFormMultipleChoiceBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"

void UGFormMultipleChoiceHorizontalBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);

	KnownBoxes.Empty();

	TArray<UWidget*> Children = GetAllChildren();

	for (size_t i = 0; i < Children.Num(); i++)
	{
		if (UGFormMultipleChoiceBox* CastedChild = Cast<UGFormMultipleChoiceBox>(Children[i]))
		{
			//Add the functionality for when a Multiple Choice Box is selected
			CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(this, &UGFormMultipleChoiceHorizontalBox::OnCheckBoxSelected);

			KnownBoxes.Add(CastedChild);
		}
	}
}

void UGFormMultipleChoiceHorizontalBox::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	for (UGFormMultipleChoiceBox* Box : KnownBoxes)
	{
		if (Box == NewSelection)
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

TArray<FGFormInformation> UGFormMultipleChoiceHorizontalBox::GetFormDetails()
{
	return TArray<FGFormInformation>();
}
