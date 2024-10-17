// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormTickBoxHorizontalBox.h"
#include "GFormTickBox.h"

void UGFormTickBoxHorizontalBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	if (!WidgetData)
		WidgetData = NewObject<UGFormDataComponent>(this);

	TArray<UWidget*> Children = GetAllChildren();

	for (size_t i = 0; i < Children.Num(); i++)
	{
		if (UGFormTickBox* CastedChild = Cast<UGFormTickBox>(Children[i]))
		{
			//Add the functionality for when a Multiple Choice Box is selected
			CastedChild->OnTickBoxChecked.AddUniqueDynamic(this, &UGFormTickBoxHorizontalBox::OnTickBoxSelected);
		}
	}
}

void UGFormTickBoxHorizontalBox::OnTickBoxSelected(UGFormTickBox* NewSelection, bool Choice)
{
	Choice ? TickedBoxes.Add(NewSelection) : TickedBoxes.Remove(NewSelection);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(TickedBoxes.Num()));
}
