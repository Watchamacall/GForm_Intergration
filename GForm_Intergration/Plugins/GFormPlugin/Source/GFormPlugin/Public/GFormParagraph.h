// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormInterface.h"
#include "Components/MultiLineEditableTextBox.h"
#include "GFormParagraph.generated.h"

/**
 * 
 */
UCLASS()
class GFORMPLUGIN_API UGFormParagraph : public UMultiLineEditableTextBox, public IGFormInterface
{
	GENERATED_BODY()

protected:
	virtual void OnWidgetRebuilt() override;
	virtual void SynchronizeProperties() override;

	UFUNCTION()
	virtual void GFormTextCommitted(const FText& NewText, ETextCommit::Type CommitMethod);

public:
	virtual TArray<FGFormInformation> GetFormDetails() override;
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override
	{
		return NSLOCTEXT("UMG", "GFormCategory", "GForm");
	}
#endif

public:
	/*
	* The Data Component which holds all information about the Form Instance
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GForm")
	UGFormDataComponent* WidgetData;
};
