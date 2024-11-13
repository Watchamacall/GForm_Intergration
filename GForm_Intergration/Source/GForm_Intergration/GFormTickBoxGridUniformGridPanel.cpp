// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTickBoxGridUniformGridPanel.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UniformGridSlot.h"
#include "GFormTickBox.h"

void UGFormTickBoxGridUniformGridPanel::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);

	KnownBoxes.Empty();

	TArray<UWidget*> Children = GetAllChildren();

	for (size_t i = 0; i < Children.Num(); i++)
	{
		if (UGFormTickBox* CastedChild = Cast<UGFormTickBox>(Children[i]))
		{
			//Add the functionality for when a Multiple Choice Box is selected
			CastedChild->OnTickBoxChecked.AddUniqueDynamic(this, &UGFormTickBoxGridUniformGridPanel::OnCheckBoxSelected);

			if (auto UniformGridSlot = Cast<UUniformGridSlot>(CastedChild->Slot))
			{
				int GridRow = UniformGridSlot->GetRow();
				int ColumnRow = UniformGridSlot->GetColumn();

				//Checking to see if the Row wanted is bigger than the Outer TArray
				if (GridRow >= KnownBoxes.Num())
				{
					KnownBoxes.SetNum(GridRow + 1);
				}
				//Checking to see if the Column is bigger than the Inner TArray
				if (ColumnRow >= KnownBoxes[GridRow].Num())
				{
					KnownBoxes[GridRow].SetNum(ColumnRow + 1);
				}

				if (KnownBoxes[GridRow][ColumnRow])
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("TickBox ") + *CastedChild->GetName() + FString(" is set inside another TickBox ") + *KnownBoxes[GridRow][ColumnRow]->GetName());
				}
				else
				{
					KnownBoxes[GridRow][ColumnRow] = CastedChild;
				}
			}
		}
	}
}

void UGFormTickBoxGridUniformGridPanel::OnCheckBoxSelected(UGFormTickBox* NewSelection, bool Choice)
{
	int RowToGoThrough = Cast<UUniformGridSlot>(NewSelection->Slot)->GetRow();

	for (UGFormTickBox* Box : KnownBoxes[RowToGoThrough])
	{
		if (Box == NewSelection)
		{
			FString RowEntryID = KnownBoxes[RowToGoThrough][0]->WidgetData->GetEntryData(0).EntryID;

			int Column = Cast<UUniformGridSlot>(NewSelection->Slot)->GetColumn();

			FString ColumnData = KnownBoxes[0][Column]->WidgetData->GetEntryData(0).EntryData;

			//Either Add or Remove Entry Data based what is has been chosen to do
			Choice ? 
				WidgetData->AddEntryData(RowEntryID, *ColumnData) : 
				WidgetData->RemoveEntryData(RowEntryID, *ColumnData);
		}
	}
}

TArray<FGFormInformation> UGFormTickBoxGridUniformGridPanel::GetFormDetails()
{
	return WidgetData->EntryData;
}
