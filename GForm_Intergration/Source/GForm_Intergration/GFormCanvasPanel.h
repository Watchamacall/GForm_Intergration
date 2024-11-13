// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include <GenericPlatform/GenericPlatformHttp.h>
#include "GFormInterface.h"
#include "GFormCanvasPanel.generated.h"


/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormCanvasPanel : public UCanvasPanel
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

	FString FullDataString;

public:
	void FinishData();

protected:
	/*
	* Called when the data wants to be collected
	*/
	UFUNCTION(BlueprintCallable, Category = "GForm|Data")
	void CollectChildrenData();

	void CollectAllChildren(UWidget* ParentWidget, TArray<UWidget*>& OutChildren);

	/*
	* Encodes the data within the FString to enable it to be sent through a URL (Uses UTF8 Encoding)
	*/
	UFUNCTION(BlueprintCallable, Category = "GForm|Data")
	FString EncodeData(FString DataToEncode);

	/*
	* Adds the relevant information from Data into the bank of sending data
	*/
	void AddEncodedData(FGFormInformation Data);
};
