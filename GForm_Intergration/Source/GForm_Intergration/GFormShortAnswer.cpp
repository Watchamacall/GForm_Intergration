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

	OnTextChanged.AddUniqueDynamic(this, &UGFormShortAnswer::GFormTextCommitted);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Data has been added to the main area!"));
}

void UGFormShortAnswer::GFormTextCommitted(const FText& NewText)
{
	WidgetData->ReplaceEnteredData(0, *NewText.ToString());
}

TArray<FGFormInformation> UGFormShortAnswer::GetFormDetails()
{
	return WidgetData->EntryData;
}

