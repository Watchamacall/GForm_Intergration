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
	/*
	* Initalises the Multiple Choice Panel Widget with all the required logic to setup the GFormWidget
	* StartNum will only be used on LinearScale and Rating
	*/
	static void InitialiseComponent(UGFormDataComponent*& WidgetData, UPanelWidget* Panel, TArray<UGFormMultipleChoiceBox*>& KnownBoxes, int32 StartNum = 0);

	/*
	* Handles the logic when pressing a MultipleChoiceBox, does all the hard work for you
	*/
	static void HandleSelectedMultipleChoiceBox(UGFormDataComponent* WidgetData, UGFormMultipleChoiceBox* SelectedMultipleChoiceBox, bool Choice, TArray<UGFormMultipleChoiceBox*>& KnownBoxes);

	/*
	* Checking the Overhead 
	*/
	static void LinearScaleOverheadCheck(UPanelWidget* Panel, TArray<UGFormMultipleChoiceBox*>& KnownBoxes, int32 StartNum = 0);
};
