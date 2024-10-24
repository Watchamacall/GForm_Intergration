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
	
	for (auto KnownRow : KnownBoxes)
	{
		FString RowEntryID = KnownRow[0]->WidgetData->GetEntryData(0).EntryID;

		if (!RowEntryID.IsEmpty())
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
			WidgetData->ReplaceEnteredData(RowToGoThrough, *Box->WidgetData->GetEntryData(0).EntryData);
		}
		else if (Box->GetCheckedState() == ECheckBoxState::Checked)
		{
			Box->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}

TArray<FGFormInformation> UGFormMultipleChoiceBoxUniformGridPanel::GetFormDetails()
{
	/*
	* Get the Entry ID from the WidgetData and link it to the EnteredData which is the option which has been chosen from the ComboBox Value
	*/

	TArray<FGFormInformation> ReturnArray;

	for (size_t Row = 0; Row < KnownBoxes.Num(); Row++)
	{
		for (size_t Column = 0; Column < KnownBoxes[Row].Num(); Column++)
		{

		}
	}
	//ReturnArray.Add(FGFormInformation(WidgetData->GetEntryID(), WidgetData->GetAllEnteredData()[0]));

	return ReturnArray; 
}
