// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormParagraph.h"

void UGFormParagraph::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);
}

void UGFormParagraph::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnTextCommitted.AddUniqueDynamic(this, &UGFormParagraph::GFormTextCommitted);
}

void UGFormParagraph::GFormTextCommitted(const FText& NewText, ETextCommit::Type CommitMethod)
{
	WidgetData->ReplaceEnteredData(0, *NewText.ToString());
}

TArray<FGFormInformation> UGFormParagraph::GetFormDetails()
{
	return WidgetData->EntryData;
}
