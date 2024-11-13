// Fill out your copyright notice in the Description page of Project Settings.

#include "GFormMultipleChoiceBox.h"

void UGFormMultipleChoiceBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);

	OnCheckStateChanged.AddUniqueDynamic(this, &UGFormMultipleChoiceBox::CheckBoxDelegateRun);
}

void UGFormMultipleChoiceBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UGFormMultipleChoiceBox::CheckBoxDelegateRun(bool HasChecked)
{
		OnMultipleChoiceBoxChecked.Broadcast(this, HasChecked);
}

TArray<FGFormInformation> UGFormMultipleChoiceBox::GetFormDetails()
{
	return WidgetData->EntryData;
}
