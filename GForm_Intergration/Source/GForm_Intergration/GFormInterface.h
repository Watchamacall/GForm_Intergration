// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GFormInterface.generated.h"

class UGFormDataComponent;
struct FGFormInformation;

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UGFormInterface : public UInterface
{
	GENERATED_BODY()
};

class GFORM_INTERGRATION_API IGFormInterface
{
	GENERATED_BODY()
public:

    /*
    * Implementation of getting the Form Details in the format of the FGFormInformation Struct
    */
	virtual TArray<FGFormInformation> GetFormDetails();
};
