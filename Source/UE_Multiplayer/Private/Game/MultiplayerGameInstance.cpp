// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MultiplayerGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// 
/// </summary>
UMultiplayerGameInstance::UMultiplayerGameInstance()
{
	ConstructorHelpers::FClassFinder<UMainMenu>MenuWidget(TEXT("/Game/UIs/WBP_MenuWidget"));
	ConstructorHelpers::FClassFinder<UJoinWidget>JoinWidget(TEXT("/Game/UIs/WBP_JoinWidget"));
	ConstructorHelpers::FClassFinder<UListItems>ListItm(TEXT("/Game/UIs/WBP_Items"));
	if (MenuWidget.Class)
	{
		MWidget = MenuWidget.Class;
	}
	if (JoinWidget.Class)
	{
		JWidget = JoinWidget.Class;
	}
	if (ListItm.Class)
	{
		WBP_ListItm = ListItm.Class;
	}

}

void UMultiplayerGameInstance::Init()
{
	MyOnlineSubsystem = IOnlineSubsystem::Get();
	if (MyOnlineSubsystem)
	{
		UE_LOG(LogTemp, Display, TEXT("Online Subsystem is Valid"));
		SessionInterface = MyOnlineSubsystem->GetSessionInterface();
		if (!SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("SessionInterface InValid"));
		}
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Online Subsystem InValid"));
	SessSettings.bIsLANMatch = true;
	SessSettings.NumPublicConnections = 2;
	SessSettings.bShouldAdvertise = true;
	MenuWidgetRef = CreateWidget<UMainMenu>(GetWorld(), MWidget, FName("MainMenuWidget"));
	MenuWidgetRef->AddToViewport(); MenuWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	JoinWidgetRef = CreateWidget<UJoinWidget>(GetWorld(), JWidget, FName("JoinWidget"));
	JoinWidgetRef->AddToViewport(); JoinWidgetRef->SetVisibility(ESlateVisibility::Collapsed);// JoinWidgetRef->GInstance = this;
}

void UMultiplayerGameInstance::Host()
{
	if (SessionInterface->GetNamedSession("MyGameSession"))
	{
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionDestroyComplete);
		SessionInterface->DestroySession("MyGameSession");
	}
	else
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionCreatedComplete);
		SessionInterface->CreateSession(0, TEXT("MyGameSession"), SessSettings);
	}
}

void UMultiplayerGameInstance::Join(const FString& IP)
{
	FindSessions();
	/*if (!ensure(GetWorld() != nullptr)) return;

	APlayerController* FirstPlayerController = GetFirstLocalPlayerController();
	if (!ensure(FirstPlayerController != nullptr)) return;
	FirstPlayerController->ClientTravel(IP, ETravelType::TRAVEL_Absolute);
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Joined"));*/
}

void UMultiplayerGameInstance::ShowWidget(int32 Number)
{
	switch (Number)
	{
	case 1:
	{
		MenuWidgetRef = CreateWidget<UMainMenu>(GetWorld(), MWidget, FName("MainMenuWidget"));
		MenuWidgetRef->AddToViewport();
		//MenuWidgetRef->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	case 2:
	{
		JoinWidgetRef->SetVisibility(ESlateVisibility::Visible);
	}
	}
}

void UMultiplayerGameInstance::HideWidget()
{
	MenuWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	JoinWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
}

void UMultiplayerGameInstance::OnSessionCreatedComplete(FName SessionName, bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Display, TEXT("Session Iniated Successfully"));
		if (!ensure(GetWorld() != nullptr)) return;

		GetWorld()->ServerTravel("/Game/Levels/PlayMap?listen");
		GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Session Failed to Iniate"));
}

void UMultiplayerGameInstance::OnSessionDestroyComplete(FName SessionName, bool bSuccess)
{
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionCreatedComplete);
	SessionInterface->CreateSession(0, TEXT("MyGameSession"), SessSettings);
}

void UMultiplayerGameInstance::FindSessions()
{
	//SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionsSearched);
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

//void UMultiplayerGameInstance::OnSessionsSearched(bool success)
//{
//	UE_LOG(LogTemp, Display, TEXT("Session Searching Completed"));
//	if (success && SessionSearch.IsValid())
//	{
//		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
//		{
//			UE_LOG(LogTemp, Display, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
//			JoinWidgetRef->AddServer(FText::FromString(SearchResult.GetSessionIdStr()));
//		}
//	}
//}
