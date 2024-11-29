// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GenericPlatform/GenericPlatformHttp.h>
#include "GFormInterface.h"
#include "Http.h"
#include "Blueprint/UserWidget.h"
#include "GFormUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GFORMPLUGIN_API UGFormUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*
	* The URL Specifier Code for sending the form.
	* Located:
	* https://docs.google.com/forms/d/e/<HERE>1FAIpQLSd3JBxVnHTyRZZbFWQk4UY6v2EOryPgfHPLh2kN4qUzlmMwy</HERE>/viewform?
	* Only place the string of Alphanumerical values!
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GForm|URL")
	FString URLCode;

	const FString GFormURLPreContentStartString = "https://docs.google.com/forms/d/e/";
	const FString GFormURLPreContentEndString = "/formResponse?submit=Submit?usp=pp_url";

protected:
	/*
	* The String containing all &entry.000=XXX elements
	*/
	FString FullDataString;

public:

	UFUNCTION()
	void FinishData();

	UFUNCTION(BlueprintImplementableEvent, Category = "GForm")
	void OnFormSent(int32 ResponseCode, const FString& ResponseString, const bool WasSuccessful);

protected:

	virtual void OnWidgetRebuilt() override;

	/*
	* Called when the data wants to be collected
	*/
	UFUNCTION(BlueprintCallable, Category = "GForm|Data")
	void CollectChildrenData();

	/*
	* Collects all children from this Widget including children of children and places them in the OutChildren Array
	*/
	void CollectAllChildren(TArray<UWidget*>& OutChildren);

	void OnFormSentInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);

	/*
	* Adds the relevant information from Data into the bank of sending data
	*/
	void AddEncodedData(FGFormInformation Data);

};
