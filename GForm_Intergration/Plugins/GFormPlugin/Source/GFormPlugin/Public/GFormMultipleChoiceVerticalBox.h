// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "Components/VerticalBox.h"
#include "GFormMultipleChoiceVerticalBox.generated.h"

class GFormMultipleChoiceBox;

/**
 * 
 */
UCLASS()
class GFORMPLUGIN_API UGFormMultipleChoiceVerticalBox : public UVerticalBox, public IGFormInterface
{
	GENERATED_BODY()

protected:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;

	TArray<UGFormMultipleChoiceBox*> KnownBoxes;

public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override
	{
		return NSLOCTEXT("UMG", "GFormCategory", "GForm");
	}
#endif
protected:
	virtual void OnWidgetRebuilt() override;

public:

	/*
	* Called when a Multiple Choice Box has been triggered as "ON" and calls this to shut off the other choices
	*/
	UFUNCTION()
	virtual void OnCheckBoxSelected(UGFormMultipleChoiceBox* NewSelection, bool Choice);

public:
	virtual TArray<FGFormInformation> GetFormDetails() override;

};
