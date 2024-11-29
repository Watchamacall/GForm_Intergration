// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormMultipleChoiceBoxUniformGridPanel.h"
#include "GFormMultipleChoiceBox.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"


void UGFormMultipleChoiceBoxUniformGridPanel::OnWidgetRebuilt()
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
			CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(this, &UGFormMultipleChoiceBoxUniformGridPanel::OnCheckBoxSelected);

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
					KnownBoxes[GridRow].SetNum(ColumnRow+1);
				}

				if (KnownBoxes[GridRow][ColumnRow])
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("Multiple CheckBox ") + *CastedChild->GetName() + FString(" is set inside another Multiple CheckBox ") + *KnownBoxes[GridRow][ColumnRow]->GetName());
				}
				else
				{
					KnownBoxes[GridRow][ColumnRow] = CastedChild;
				}
			}
		}
	}
	
	for (auto& KnownRow : KnownBoxes)
	{
		//Get the first element of the KnownRow
		FString RowEntryID = KnownRow[0]->WidgetData->GetEntryData(0).EntryID;

		if (RowEntryID.IsEmpty())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Entry ID for one of the rows is invalid. Ensure the First Element of each Row and Column has the correct information!"));
		}
		else
		{
			WidgetData->AddEntryData(RowEntryID, "");
		}
	}
}

void UGFormMultipleChoiceBoxUniformGridPanel::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	int RowToGoThrough = Cast<UUniformGridSlot>(NewSelection->Slot)->GetRow();

	for (UGFormMultipleChoiceBox* Box : KnownBoxes[RowToGoThrough])
	{
		if (Box == NewSelection)
		{
			//Because only the first row and column will have data provided, need to get the appropriate data
			int ColumnNum = Cast<UUniformGridSlot>(Box->Slot)->GetColumn();
			FString ColumnData = KnownBoxes[0][ColumnNum]->WidgetData->GetEntryData(0).EntryData;

			if (ColumnData.IsEmpty())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Column within a Multiple Choice Box is invalid, check all first columns and ensure that they have the appropriate Entry Data!"));
			}
			//Changes the EntryData of the provided Row
			WidgetData->ReplaceEnteredData(RowToGoThrough, *ColumnData);

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

TArray<FGFormInformation> UGFormMultipleChoiceBoxUniformGridPanel::GetFormDetails()
{
	return WidgetData->EntryData; 
}
