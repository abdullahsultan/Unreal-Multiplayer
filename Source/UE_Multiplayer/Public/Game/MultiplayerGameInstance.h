// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "UE_Multiplayer/Public/UI/ListItems.h"
#include "UE_Multiplayer/Public/UI/JoinWidget.h"
#include "UE_Multiplayer/Public/UI/MainMenu.h"
#include "MultiplayerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE_MULTIPLAYER_API UMultiplayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UMultiplayerGameInstance();
	
	void Init() override;

 
public:
	TSubclassOf<UUserWidget> MWidget;
	TSubclassOf<UUserWidget> JWidget;
	TSubclassOf<UListItems> WBP_ListItm;

	IOnlineSubsystem* MyOnlineSubsystem;
	IOnlineSessionPtr SessionInterface;
	FOnlineSessionSettings SessSettings;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	UPROPERTY(BlueprintReadWrite)
	UMainMenu* MenuWidgetRef;
	
	UPROPERTY(BlueprintReadWrite)
	UJoinWidget* JoinWidgetRef;

	FString ServerNameToHost;

	UFUNCTION(BlueprintCallable)
		void ShowWidget(int32 Number);
	UFUNCTION(BlueprintCallable)
		void HideWidget();

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& IP, int32 SessionNo);


	UFUNCTION()
		void OnSessionCreatedComplete(FName SessionName, bool bSuccess);
	UFUNCTION()
		void OnSessionDestroyComplete(FName SessionName, bool bSuccess);
	
	UFUNCTION()
	void FindSessions();

	UFUNCTION()
		void OnSessionsSearched(bool success);

	void OnJoinSessionCompletes(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
