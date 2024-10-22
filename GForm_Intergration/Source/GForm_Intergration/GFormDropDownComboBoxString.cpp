// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormDropDownComboBoxString.h"

void UGFormDropDownComboBoxString::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);
	
	OnSelectionChanged.AddUniqueDynamic(this, &UGFormDropDownComboBoxString::ComboBoxValueChanged);
}

void UGFormDropDownComboBoxString::ComboBoxValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	WidgetData->GetAllEnteredData().Empty();
	
	WidgetData->AddEnteredData(FText::FromString(SelectedItem));
}

TArray<FGFormInformation> UGFormDropDownComboBoxString::GetFormDetails()
{
	/*
	* Get the Entry ID from the WidgetData and link it to the EnteredData which is the option which has been chosen from the ComboBox Value
	*/

	TArray<FGFormInformation> ReturnArray;

	ReturnArray.Add(FGFormInformation(WidgetData->GetEntryID(), WidgetData->GetAllEnteredData()[0]));
	
	return ReturnArray;
}


