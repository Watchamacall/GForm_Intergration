// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "Components/ComboBoxString.h"
#include "GFormDropDownComboBoxString.generated.h"

/**
 * 
 */
UCLASS()
class GFORMPLUGIN_API UGFormDropDownComboBoxString : public UComboBoxString, public IGFormInterface
{
	GENERATED_BODY()
	
public:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;

public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override
{
	return NSLOCTEXT("UMG", "GFormCategory", "GForm");
}
#endif
protected:

	virtual void OnWidgetRebuilt() override;

	/*
	* Called when a Multiple Choice Box has been triggered as "ON" and calls this to shut off the other choices
	*/
	UFUNCTION()
	virtual void ComboBoxValueChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	virtual TArray<FGFormInformation> GetFormDetails() override;
};
