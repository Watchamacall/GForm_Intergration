// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormUniversalGridPanel.h"
#include "GFormMultipleChoiceBox.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"


void UGFormUniversalGridPanel::OnWidgetRebuilt()
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
			CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(this, &UGFormUniversalGridPanel::OnCheckBoxSelected);

			auto UniformGridSlot = Cast<UUniformGridSlot>(CastedChild->GetContentSlot());

			KnownBoxes[UniformGridSlot->GetRow()].Add(CastedChild);
		}
	}
}

void UGFormUniversalGridPanel::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	for (TArray<UGFormMultipleChoiceBox*> Boxes : KnownBoxes)
	{
		for (UGFormMultipleChoiceBox* Box : Boxes)
		{
			if (Box == NewSelection)
			{
				WidgetData->SetEnteredData(Box->WidgetData->GetEnteredData());
			}
			else if (Box->GetCheckedState() == ECheckBoxState::Checked)
			{
				Box->SetCheckedState(ECheckBoxState::Unchecked);
			}
		}
	}
}
