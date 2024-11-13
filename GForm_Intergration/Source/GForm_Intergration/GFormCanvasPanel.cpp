// Fill out your copyright notice in the Description page of Project Settings.


#include "GFormCanvasPanel.h"
#include "GFormWidgetSecondaryClass.h"
#include "GFormTickBox.h"
#include "GFormMultipleChoiceBox.h"
#include "Http.h"

void UGFormCanvasPanel::FinishData()
{
	CollectChildrenData();

	FString SendingURL = GFormURLPreContentStartString + URLCode + GFormURLPreContentEndString + FullDataString;

	FHttpModule* Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetURL(SendingURL);

	Request->SetVerb("POST");

	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				UE_LOG(LogTemp, Log, TEXT("HTTP Response Code: %d"), Response->GetResponseCode());
				UE_LOG(LogTemp, Log, TEXT("Response Content: %s"), *Response->GetContentAsString());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("HTTP Request failed or response was invalid!"));
			}
		});

	Request->ProcessRequest();
}

void UGFormCanvasPanel::CollectChildrenData()
{
	TArray<UWidget*> Children;
	CollectAllChildren(this, Children);

	FullDataString.Empty();

	for (auto Child : Children)
	{
		if (auto Interface = Cast<IGFormInterface>(Child))
		{
			for (auto& Information : Interface->GetFormDetails())
			{
				Information.EntryData = EncodeData(Information.EntryData);

				AddEncodedData(Information);
			}
		}
	}
}

void UGFormCanvasPanel::CollectAllChildren(UWidget* ParentWidget, TArray<UWidget*>& OutChildren)
{
	if (!ParentWidget)
	{
		return;
	}

	// Cast to PanelWidget to access children
	UPanelWidget* Panel = Cast<UPanelWidget>(ParentWidget);
	if (Panel)
	{
		// Iterate over direct children
		for (int32 i = 0; i < Panel->GetChildrenCount(); ++i)
		{
			UWidget* ChildWidget = Panel->GetChildAt(i);
			if (ChildWidget)
			{
				if (!ChildWidget->IsA<UGFormTickBox>() && !ChildWidget->IsA<UGFormMultipleChoiceBox>())
				{
					OutChildren.Add(ChildWidget);
				}

				// Recursively collect children of the current child
				CollectAllChildren(ChildWidget, OutChildren);
			}
		}
	}
}

FString UGFormCanvasPanel::EncodeData(FString DataToEncode)
{
	return FGenericPlatformHttp::UrlEncode(DataToEncode);
}

void UGFormCanvasPanel::AddEncodedData(FGFormInformation Data)
{
	FString MainData = "&entry." + Data.EntryID + "=" + Data.EntryData;
	FullDataString.Append(MainData);
}
