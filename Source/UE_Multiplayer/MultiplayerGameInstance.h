// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
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

	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString& IP);

	UFUNCTION(BlueprintCallable)
		void LoadMenu();

	TSubclassOf<UUserWidget> MWidget;
};
