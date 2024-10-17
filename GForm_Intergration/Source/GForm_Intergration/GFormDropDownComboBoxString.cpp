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
	WidgetData->SetEnteredData(FText::FromString(SelectedItem));
}


