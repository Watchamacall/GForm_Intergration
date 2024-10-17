// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "Components/HorizontalBox.h"
#include "GFormTickBoxHorizontalBox.generated.h"

class UGFormTickBox;

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormTickBoxHorizontalBox : public UHorizontalBox
{
	GENERATED_BODY()
	
public:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;

protected:
	/*
	* The EnteredData for all the TickBoxes that have been ticked
	*/
	UPROPERTY(VisibleAnywhere, Category = "GForm|Data")
	TArray<UGFormTickBox*> TickedBoxes;

protected:

	virtual void OnWidgetRebuilt() override;

	/*
	* Called when a Multiple Choice Box has been triggered as "ON" and calls this to shut off the other choices
	*/	
	UFUNCTION()
	virtual void OnTickBoxSelected(UGFormTickBox* NewSelection, bool Choice);
};
