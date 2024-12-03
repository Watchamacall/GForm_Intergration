// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormShortAnswer.h"
#include "Components/PanelWidget.h"

void UGFormShortAnswer::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);
}

void UGFormShortAnswer::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnTextCommitted.AddUniqueDynamic(this, &UGFormShortAnswer::GFormTextCommitted);
}

void UGFormShortAnswer::GFormTextCommitted(const FText& NewText, ETextCommit::Type CommitMethod)
{
	WidgetData->ReplaceEnteredData(0, *NewText.ToString());
}

TArray<FGFormInformation> UGFormShortAnswer::GetFormDetails()
{
	return WidgetData->EntryData;
}

