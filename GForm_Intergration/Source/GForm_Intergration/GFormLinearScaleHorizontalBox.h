// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "Components/HorizontalBox.h"
#include "GFormLinearScaleHorizontalBox.generated.h"

class UGFormMultipleChoiceBox;

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormLinearScaleHorizontalBox : public UHorizontalBox, public IGFormInterface
{
	GENERATED_BODY()
	
protected:
	/*
	* The minimum value the Linear Scale will go to
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GForm|Linear Scale", meta=(ClampMin=0, ClampMax=1))
	int MinimumValue = 0;

	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;

	TArray<UGFormMultipleChoiceBox*> KnownBoxes;
protected:
	virtual void OnWidgetRebuilt() override;

	/*
	* Called when a Multiple Choice Box has been triggered as "ON" and calls this to shut off the other choices
	*/
	UFUNCTION()
	virtual void OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice);

	virtual TArray<FGFormInformation> GetFormDetails() override;

};
