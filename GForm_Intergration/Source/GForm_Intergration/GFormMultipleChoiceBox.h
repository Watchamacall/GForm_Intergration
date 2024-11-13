// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CheckBox.h"
#include "GFormInterface.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormMultipleChoiceBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMultipleChoiceBoxChecked, UGFormMultipleChoiceBox*, SelfBox, bool, HasChecked);

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormMultipleChoiceBox : public UCheckBox, public IGFormInterface
{
	GENERATED_BODY()
protected:

	virtual void OnWidgetRebuilt() override;
	virtual void SynchronizeProperties() override;

	UFUNCTION()
	virtual void CheckBoxDelegateRun(bool HasChecked);

public:
	virtual TArray<FGFormInformation> GetFormDetails() override;


public:
	/*
	* Called when the CheckBox has been Changed
	*/
	FOnMultipleChoiceBoxChecked OnMultipleChoiceBoxChecked;

	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;
};
