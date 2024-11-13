// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "GFormSubmitButton.generated.h"

class UGFormCanvasPanel;
/**
 * 
 */
UCLASS()
class GFORM_INTERGRATION_API UGFormSubmitButton : public UButton
{
	GENERATED_BODY()

protected:
	virtual void OnWidgetRebuilt() override;

	UFUNCTION()
	void GFormClickedFunction();

	template <typename T>
	T* GetTypedParent(UWidget* Widget);
};

template<typename T>
inline T* UGFormSubmitButton::GetTypedParent(UWidget* Widget)
{
    if (!Widget)
    {
        return nullptr;
    }

    auto TypedParent = Widget->GetParent();
    if (!TypedParent)
    {
        return nullptr;
    }

    while (!TypedParent->IsA(T::StaticClass()))
    {
        TypedParent = TypedParent->GetParent();

        if (!TypedParent)
        {
            return nullptr;
        }
    }

    return Cast<T>(TypedParent);
}
