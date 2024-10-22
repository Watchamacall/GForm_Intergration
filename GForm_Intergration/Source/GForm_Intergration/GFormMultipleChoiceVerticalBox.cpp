// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormMultipleChoiceVerticalBox.h"
#include "GFormMultipleChoiceBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"

void UGFormMultipleChoiceVerticalBox::OnWidgetRebuilt()
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
			CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(this, &UGFormMultipleChoiceVerticalBox::OnCheckBoxSelected);

			KnownBoxes.Add(CastedChild);
		}
	}
}

void UGFormMultipleChoiceVerticalBox::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	for (UGFormMultipleChoiceBox* Box : KnownBoxes)
	{
		if (Box == NewSelection)
		{
			WidgetData->GetAllEnteredData().Empty();
			WidgetData->AddEnteredData(FText::FromString(Box->WidgetData->GetAllEnteredData()[0]));
		}
		else if (Box->GetCheckedState() == ECheckBoxState::Checked)
		{
			Box->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}