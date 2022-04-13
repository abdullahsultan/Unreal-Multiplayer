// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
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

	IOnlineSubsystem* MyOnlineSubsystem;
	IOnlineSessionPtr SessionInterface;
	FOnlineSessionSettings SessSettings;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* MenuWidgetRef;
	
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* JoinWidgetRef;

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& IP);

	UFUNCTION(BlueprintCallable)
		void ShowWidget(int32 Number);
	UFUNCTION(BlueprintCallable)
		void HideWidget();

	UFUNCTION()
		void OnSessionCreatedComplete(FName SessionName, bool bSuccess);
	UFUNCTION()
		void OnSessionDestroyComplete(FName SessionName, bool bSuccess);

	void FindSessions();

	UFUNCTION()
		void OnSessionsSearched(bool success);

};
