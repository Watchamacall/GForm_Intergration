// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "Components/UniformGridPanel.h"
#include "GFormUniversalGridPanel.generated.h"

class GFormMultipleChoiceBox;

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormUniversalGridPanel : public UUniformGridPanel
{
	GENERATED_BODY()

protected:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;

	TArray<TArray<UGFormMultipleChoiceBox*>> KnownBoxes;
protected:
	virtual void OnWidgetRebuilt() override;

	/*
	* Called when a Multiple Choice Box has been triggered as "ON" and calls this to shut off the other choices
	*/
	UFUNCTION()
	virtual void OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice);

};
