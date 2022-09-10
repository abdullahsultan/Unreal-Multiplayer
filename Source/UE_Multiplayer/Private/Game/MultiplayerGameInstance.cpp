// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MultiplayerGameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/OnlineSessionInterface.h"

static const FName HostingSessionSettingsKey = "MultiPlayerKey";
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
/*
				//////////////////////////////Widgets Settings//////////////////////////////
*/
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
/*
				//////////////////////////////Init//////////////////////////////
*/
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
	SessSettings.bUsesPresence = true;
	SessSettings.bUseLobbiesIfAvailable = true;
	MenuWidgetRef = CreateWidget<UMainMenu>(GetWorld(), MWidget, FName("MainMenuWidget"));
	MenuWidgetRef->AddToViewport(); MenuWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	JoinWidgetRef = CreateWidget<UJoinWidget>(GetWorld(), JWidget, FName("JoinWidget"));
	JoinWidgetRef->AddToViewport(); JoinWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionDestroyComplete);
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionCreatedComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnSessionsSearched);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiplayerGameInstance::OnJoinSessionCompletes);
}



void UMultiplayerGameInstance::Host()
{
	UE_LOG(LogTemp, Warning, TEXT("HostingBegin %s"), *ServerNameToHost);
	SessSettings.Set(HostingSessionSettingsKey, ServerNameToHost, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	if (SessionInterface->GetNamedSession("MyGameSession"))
	{
		SessionInterface->DestroySession("MyGameSession");
	}
	else
	{
		SessionInterface->CreateSession(0, TEXT("MyGameSession"), SessSettings);
	}
}

void UMultiplayerGameInstance::Join(const FString& IP, int32 SessionNo)
{
	SessionInterface->JoinSession(0,FName(*IP), SessionSearch->SearchResults[SessionNo]);
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
	SessionInterface->CreateSession(0, TEXT("MyGameSession"), SessSettings);
}

void UMultiplayerGameInstance::FindSessions()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	if (SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UMultiplayerGameInstance::OnSessionsSearched(bool success)
{
	UE_LOG(LogTemp, Display, TEXT("Session Searching Completed"));
	if (success && SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Display, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
		}
	}
}

void UMultiplayerGameInstance::OnJoinSessionCompletes(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	APlayerController* FirstPlayerController = GetFirstLocalPlayerController();
	if (!ensure(FirstPlayerController != nullptr)) return;
	FString AddressToConnect;
	if (!SessionInterface->GetResolvedConnectString(SessionName, AddressToConnect))
	{
		UE_LOG(LogTemp, Error, TEXT("ResolvedString Failed")); return;
	}
	FirstPlayerController->ClientTravel(AddressToConnect, ETravelType::TRAVEL_Absolute);
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Joined"));
}
