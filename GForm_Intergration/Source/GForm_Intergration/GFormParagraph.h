// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "Components/MultiLineEditableTextBox.h"
#include "GFormParagraph.generated.h"

/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormParagraph : public UMultiLineEditableTextBox
{
	GENERATED_BODY()

protected:
	virtual void OnWidgetRebuilt() override;
	virtual void SynchronizeProperties() override;

	UFUNCTION()
	virtual void GFormTextCommitted(const FText& NewText);

public:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;
};
