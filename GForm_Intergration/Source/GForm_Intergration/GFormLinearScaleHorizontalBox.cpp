// Fill out your copyright notice in the Description page of Project Settings.



#include "GFormLinearScaleHorizontalBox.h"
#include "GFormMultipleChoiceBox.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CheckBox.h"

void UGFormLinearScaleHorizontalBox::OnWidgetRebuilt()
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
			//Checker for 11 when we can only have 10
			if (KnownBoxes.Num() >= LINEAR_SCALE_MAX && MinimumValue == 1)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Linear Scale will only work for up to 10 CheckBoxes in this format, no other ones will be counted!"));
				break;
			}
			//Checker for 12 when we can only have 11
			if (KnownBoxes.Num() > LINEAR_SCALE_MAX && MinimumValue == 0)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("The Linear Scale will only work for up to 11 CheckBoxes in this format, no other ones will be counted!"));
				break;
			}

			//Add the functionality for when a Multiple Choice Box is selected
			CastedChild->OnMultipleChoiceBoxChecked.AddUniqueDynamic(this, &UGFormLinearScaleHorizontalBox::OnCheckBoxSelected);

			//Setting the Data to be the number that it appears in the line
			CastedChild->WidgetData->AddEnteredData(FText::FromString(FString::FromInt(i + (1 * MinimumValue) ) ) );

			KnownBoxes.Add(CastedChild);
		}
	}
}

void UGFormLinearScaleHorizontalBox::OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice)
{
	for (UGFormMultipleChoiceBox* Box : KnownBoxes)
	{
		if (Box == NewSelection)
		{
			WidgetData->AddEnteredData(Box->WidgetData->GetAllEnteredData());
		}
		else if (Box->GetCheckedState() == ECheckBoxState::Checked)
		{
			Box->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}
