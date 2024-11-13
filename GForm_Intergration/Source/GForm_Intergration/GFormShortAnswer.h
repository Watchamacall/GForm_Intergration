// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EditableTextBox.h"
#include "GFormInterface.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormShortAnswer.generated.h"

class UPanelWidget;

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormShortAnswer : public UEditableTextBox, public IGFormInterface
{
	GENERATED_BODY()
	
protected:
	virtual void OnWidgetRebuilt() override;
	virtual void SynchronizeProperties() override;

	UFUNCTION()
	virtual void GFormTextCommitted(const FText& NewText);

public:
	virtual TArray<FGFormInformation> GetFormDetails() override;

public:
	
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;
};
