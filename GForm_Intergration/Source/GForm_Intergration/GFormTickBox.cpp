// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTickBox.h"

void UGFormTickBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);

	OnCheckStateChanged.AddUniqueDynamic(this, &UGFormTickBox::CheckBoxDelegateRun);
}

void UGFormTickBox::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UGFormTickBox::CheckBoxDelegateRun(bool HasChecked)
{
	OnTickBoxChecked.Broadcast(this, HasChecked);
}
