// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormSubmitButton.h"
#include "GFormCanvasPanel.h"

void UGFormSubmitButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	
	if (auto TypedOuter = GetTypedParent<UGFormCanvasPanel>(this))
	{
		OnClicked.AddUniqueDynamic(this, &UGFormSubmitButton::GFormClickedFunction);
	}
}

void UGFormSubmitButton::GFormClickedFunction()
{
	if (auto TypedOuter = GetTypedParent<UGFormCanvasPanel>(this))
	{
		TypedOuter->FinishData();
	}
}
