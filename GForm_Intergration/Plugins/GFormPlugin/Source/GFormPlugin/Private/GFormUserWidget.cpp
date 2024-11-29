// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormUserWidget.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormTickBox.h"
#include "GFormMultipleChoiceBox.h"
#include "Blueprint/WidgetTree.h"
#include "GFormSubmitButton.h"



void UGFormUserWidget::FinishData()
{
	CollectChildrenData();

	FString SendingURL = GFormURLPreContentStartString + URLCode + GFormURLPreContentEndString + FullDataString;

	//HTTP element stuffs
	FHttpModule* Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetURL(SendingURL);

	Request->SetVerb("POST");

	Request->OnProcessRequestComplete().BindUObject(this, &UGFormUserWidget::OnFormSentInternal);

	Request->ProcessRequest();
}

void UGFormUserWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	TArray<UWidget*> Children;
	WidgetTree->GetAllWidgets(Children);

	for (UWidget* Widget : Children)
	{
		if (UGFormSubmitButton* FoundButton = Cast<UGFormSubmitButton>(Widget))
		{
			FoundButton->OnClicked.AddUniqueDynamic(this, &UGFormUserWidget::FinishData);
			break;
		}
	}
}

void UGFormUserWidget::CollectChildrenData()
{
	TArray<UWidget*> Children;
	CollectAllChildren(Children);

	FullDataString.Empty();

	/*
	* Goes through each Child and check to see if there is the Interface available. If so then get the Form Details and iterate through each one, adding their data
	*/
	for (auto Child : Children)
	{
		if (auto Interface = Cast<IGFormInterface>(Child))
		{
			for (auto& Information : Interface->GetFormDetails())
			{
				AddEncodedData(Information);
			}
		}
	}
}

void UGFormUserWidget::CollectAllChildren(TArray<UWidget*>& OutChildren)
{
	TArray<UWidget*> AllChildren;
	WidgetTree->GetAllWidgets(AllChildren);

	// Iterate over direct children
	for (int32 i = 0; i < AllChildren.Num(); ++i)
	{
		UWidget* ChildWidget = AllChildren[i];
		if (ChildWidget)
		{
			//Only add if the Child is not a TickBox or a MultipleChoiceBox
			if (!ChildWidget->IsA<UGFormTickBox>() && !ChildWidget->IsA<UGFormMultipleChoiceBox>())
			{
				OutChildren.Add(ChildWidget);
			}
		}
	}
}

void UGFormUserWidget::OnFormSentInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	if (WasSuccessful && Response.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("HTTP Response Code: %d"), Response->GetResponseCode());
		UE_LOG(LogTemp, Log, TEXT("Response Content: %s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request failed or response was invalid!"));
	}

	OnFormSent(Response->GetResponseCode(), *Response->GetContentAsString(), WasSuccessful);

}

void UGFormUserWidget::AddEncodedData(FGFormInformation Data)
{
	FString MainData = "&entry." + Data.EntryID + "=" + FGenericPlatformHttp::UrlEncode(Data.EntryData);

	FullDataString.Append(MainData);
}
