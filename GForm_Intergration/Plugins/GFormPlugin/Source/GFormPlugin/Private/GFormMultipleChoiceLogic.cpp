// Fill out your copyright notice in the Description page of Project Settings.

#include "GFormMultipleChoiceLogic.h"
#include "GFormMultipleChoiceVerticalBox.h"
#include "GFormMultipleChoiceHorizontalBox.h"
#include "GFormMultipleChoiceBox.h"
#include "GFormLinearScaleVerticalBox.h"
#include "GFormLinearScaleHorizontalBox.h"
#include "GFormRatingHorizontalBox.h"
#include "GFormRatingVerticalBox.h"

void FGFormMultipleChoiceLogic::InitialiseComponent(UGFormDataComponent*& WidgetData, UPanelWidget* Panel, TArray<UGFormMultipleChoiceBox*>& KnownBoxes, int32 StartNum)
{
	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(Panel);

	KnownBoxes.Empty();

	TArray<UWidget*> Children = Panel->GetAllChildren();

	for (size_t i = 0; i < Children.Num(); i++)
	{
		if (UGFormMultipleChoiceBox* CastedChild = Cast<UGFormMultipleChoiceBox>(Children[i]))
		{
			//MULTIPLE CHOICE
			if (UGFormMultipleChoiceVerticalBox* MultipleChoiceVerticalBox = Cast<UGFormMultipleChoiceVerticalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(MultipleChoiceVerticalBox, &UGFormMultipleChoiceVerticalBox::OnCheckBoxSelected);
			}
			else if (UGFormMultipleChoiceHorizontalBox* MultipleChoiceHorizontalBox = Cast<UGFormMultipleChoiceHorizontalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(MultipleChoiceHorizontalBox, &UGFormMultipleChoiceHorizontalBox::OnCheckBoxSelected);
			}
			//LINEAR SCALE
			else if (UGFormLinearScaleVerticalBox* LinearScaleVerticalBox = Cast<UGFormLinearScaleVerticalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(LinearScaleVerticalBox, &UGFormLinearScaleVerticalBox::OnCheckBoxSelected);
				CastedChild->WidgetData->ReplaceEnteredData(0, FString::FromInt(i + StartNum));
			}
			else if (UGFormLinearScaleHorizontalBox* LinearScaleHorizontalBox = Cast<UGFormLinearScaleHorizontalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(LinearScaleHorizontalBox, &UGFormLinearScaleHorizontalBox::OnCheckBoxSelected);
				CastedChild->WidgetData->ReplaceEnteredData(0, FString::FromInt(i + StartNum));
			}
			//RATING
			else if (UGFormRatingVerticalBox* RatingVerticalBox = Cast<UGFormRatingVerticalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(RatingVerticalBox, &UGFormRatingVerticalBox::OnCheckBoxSelected);
				CastedChild->WidgetData->ReplaceEnteredData(0, FString::FromInt(i + StartNum));
			}
			else if (UGFormRatingHorizontalBox* RatingHorizontalBox = Cast<UGFormRatingHorizontalBox>(Panel))
			{
				CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(RatingHorizontalBox, &UGFormRatingHorizontalBox::OnCheckBoxSelected);
				CastedChild->WidgetData->ReplaceEnteredData(0, FString::FromInt(i + StartNum));
			}

			KnownBoxes.Add(CastedChild);
		}
	}
	//If we are Linear Scale or Rating
	if (Cast<UGFormLinearScaleVerticalBox>(Panel) || Cast<UGFormLinearScaleHorizontalBox>(Panel) || Cast<UGFormRatingVerticalBox>(Panel) || Cast<UGFormRatingHorizontalBox>(Panel))
	{
		LinearScaleOverheadCheck(Panel, KnownBoxes, StartNum);
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

void FGFormMultipleChoiceLogic::LinearScaleOverheadCheck(UPanelWidget* Panel, TArray<UGFormMultipleChoiceBox*>& KnownBoxes, int32 StartNum)
{
	//LINEAR SCALE
	if (Cast<UGFormLinearScaleVerticalBox>(Panel) || Cast<UGFormLinearScaleHorizontalBox>(Panel))
	{
		//Checker for 11 when we can only have 10
		if (KnownBoxes.Num() >= LINEAR_SCALE_MAX && StartNum == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Linear Scale will only work for up to 10 CheckBoxes in this format, no other ones will be counted!"));

			//Going from the tenth element and removing them
			for (size_t i = LINEAR_SCALE_MAX-1; i < KnownBoxes.Num(); i++)
			{
				KnownBoxes[i]->OnMultipleChoiceBoxChecked.Clear();
				KnownBoxes[i]->RemoveFromRoot();
				KnownBoxes.RemoveAt(i);
			}
		}
		//Checker for 12 when we can only have 11
		if (KnownBoxes.Num() > LINEAR_SCALE_MAX && StartNum == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Linear Scale will only work for up to 11 CheckBoxes in this format, no newer ones will work!"));

			//Going from the eleventh element and removing them
			for (size_t i = LINEAR_SCALE_MAX; i < KnownBoxes.Num(); i++)
			{
				KnownBoxes[i]->OnMultipleChoiceBoxChecked.Clear();
				KnownBoxes[i]->RemoveFromRoot();
				KnownBoxes.RemoveAt(i);
			}
		}
	}
	//RATING
	else if (Cast<UGFormRatingHorizontalBox>(Panel) || Cast<UGFormRatingVerticalBox>(Panel))
	{
		//Checker for having over 9 Checkboxes
		if (KnownBoxes.Num() > LINEAR_SCALE_MAX)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Rating will only work for up to 10 CheckBoxes, all newer ones will not function!"));

			//Any elements above 8 (element 9 because we start at 0) gets destroyed
			for (size_t i = LINEAR_SCALE_MAX; i < KnownBoxes.Num(); i++)
			{
				KnownBoxes[i]->OnMultipleChoiceBoxChecked.Clear();
				KnownBoxes[i]->RemoveFromRoot();
				KnownBoxes.RemoveAt(i);
			}
		}
	}
}
