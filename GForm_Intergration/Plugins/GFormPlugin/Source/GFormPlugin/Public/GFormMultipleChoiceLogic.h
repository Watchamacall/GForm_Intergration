// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UGFormDataComponent;
class UGFormMultipleChoiceBox;
class UPanelWidget;
/**
 * 
 */
class GFORMPLUGIN_API FGFormMultipleChoiceLogic
{
public:
	static void InitialiseComponent(UGFormDataComponent*& WidgetData, UPanelWidget* Panel, TArray<UGFormMultipleChoiceBox*>& KnownBoxes);

	static void HandleSelectedMultipleChoiceBox(UGFormDataComponent* WidgetData, UGFormMultipleChoiceBox* SelectedMultipleChoiceBox, bool Choice, TArray<UGFormMultipleChoiceBox*>& KnownBoxes);
};
