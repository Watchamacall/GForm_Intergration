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

			if (auto UniformGridSlot = Cast<UUniformGridSlot>(CastedChild->Slot))
			{
				int GridRow = UniformGridSlot->GetRow();
				int ColumnRow = UniformGridSlot->GetColumn();

				//Checking to see if the Row wanted is bigger than the Outer TArray
				if (GridRow >= KnownBoxes.Num())
				{
					KnownBoxes.SetNum(GridRow+1);
				}
				//Checking to see if the Column is bigger than the Inner TArray
				if (ColumnRow >= KnownBoxes[GridRow].Num())
				{
					KnownBoxes[GridRow].SetNumUninitialized(ColumnRow+1);
				}

				KnownBoxes[GridRow][ColumnRow] = CastedChild;
			}
		}
	}
}

void UGFormUniversalGridPanel::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	int RowToGoThrough = Cast<UUniformGridSlot>(NewSelection->Slot)->GetRow();

	for (UGFormMultipleChoiceBox* Box : KnownBoxes[RowToGoThrough])
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
