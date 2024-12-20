// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "Components/CheckBox.h"
#include "GFormTickBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTickBoxChecked, UGFormTickBox*, SelfBox, bool, HasChecked);

/**
 * 
 */
UCLASS()
class GFORMPLUGIN_API UGFormTickBox : public UCheckBox, public IGFormInterface
{
	GENERATED_BODY()
	
public:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;

	/*
	* Called when the CheckBox has been Changed
	*/
	FOnTickBoxChecked OnTickBoxChecked;
public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override
	{
		return NSLOCTEXT("UMG", "GFormCategory", "GForm");
	}
#endif

protected:

	virtual void OnWidgetRebuilt() override;

	virtual void SynchronizeProperties() override;
	
	UFUNCTION()
	virtual void CheckBoxDelegateRun(bool HasChecked);

public:
	virtual TArray<FGFormInformation> GetFormDetails() override;

};
