// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UGFormDataComponent;
class UPanelWidget;
class UGFormTickBox;
/**
 * 
 */
class GFORMPLUGIN_API FGFormTickBoxLogic
{
public:
	static void InitialiseComponent(UGFormDataComponent*& WidgetData, UPanelWidget* Panel);

	static void HandleSelectedTickBox(UGFormDataComponent* WidgetData, UGFormTickBox* SelectedTickBox, bool Choice);
};
