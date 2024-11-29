// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormRatingHorizontalBox.h"
#include "GFormMultipleChoiceBox.h"
#include "GFormMultipleChoiceLogic.h"

void UGFormRatingHorizontalBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	FGFormMultipleChoiceLogic::InitialiseComponent(WidgetData, this, KnownBoxes);
	//if (!WidgetData)
	//	WidgetData = NewObject<UGFormDataComponent>(this);

	//KnownBoxes.Empty();

	//TArray<UWidget*> Children = GetAllChildren();

	//for (size_t i = 0; i < Children.Num(); i++)
	//{
	//	if (UGFormMultipleChoiceBox* CastedChild = Cast<UGFormMultipleChoiceBox>(Children[i]))
	//	{
	//		//Checker for having over 9 Checkboxes
	//		if (KnownBoxes.Num() >= LINEAR_SCALE_MAX)
	//		{
	//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Rating will only work for up to 9 CheckBoxes, no other ones will be counted!"));
	//			break;
	//		}

	//		//Add the functionality for when a Multiple Choice Box is selected
	//		CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(this, &UGFormRatingHorizontalBox::OnCheckBoxSelected);

	//		//Setting the Data to be the number that it appears in the line
	//		CastedChild->WidgetData->ReplaceEnteredData(0, FString::FromInt(i + 1));

	//		KnownBoxes.Add(CastedChild);
	//	}
	//}
}

void UGFormRatingHorizontalBox::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	for (UGFormMultipleChoiceBox* Box : KnownBoxes)
	{
		if (Box == NewSelection)
		{
			WidgetData->ReplaceEnteredData(0, *Box->WidgetData->GetEntryData(0).EntryData);
		}
		else if (Box->GetCheckedState() == ECheckBoxState::Checked)
		{
			Box->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}

TArray<FGFormInformation> UGFormRatingHorizontalBox::GetFormDetails()
{
	return WidgetData->EntryData;
}
