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

	OnTextChanged.AddUniqueDynamic(this, &UGFormParagraph::GFormTextCommitted);

}

void UGFormParagraph::GFormTextCommitted(const FText& NewText)
{
	WidgetData->ReplaceEnteredData(0, *NewText.ToString());
}
