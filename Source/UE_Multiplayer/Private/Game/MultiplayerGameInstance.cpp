// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MultiplayerGameInstance.h"
#include "Engine/World.h"
#include <Kismet/GameplayStatics.h>

/// <summary>
/// 
/// </summary>
UMultiplayerGameInstance::UMultiplayerGameInstance() 
{
	ConstructorHelpers::FClassFinder<UUserWidget>MenuWidget(TEXT("/Game/UIs/WBP_MenuWidget"));
	ConstructorHelpers::FClassFinder<UUserWidget>JoinWidget(TEXT("/Game/UIs/WBP_JoinWidget"));
	if (MenuWidget.Class)
	{
		MWidget = MenuWidget.Class;
	}
	if (JoinWidget.Class)
	{
		JWidget = JoinWidget.Class;
	}
}

void UMultiplayerGameInstance::Init()
{
	MenuWidgetRef = CreateWidget<UUserWidget>(GetWorld(), MWidget, FName("MainMenuWidget"));
	MenuWidgetRef->AddToViewport(); MenuWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	JoinWidgetRef = CreateWidget<UUserWidget>(GetWorld(), JWidget, FName("JoinWidget"));
	JoinWidgetRef->AddToViewport(); JoinWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
}

void UMultiplayerGameInstance::Host()
{
	if (!ensure(GetWorld() != nullptr)) return;

	GetWorld()->ServerTravel("/Game/Levels/PlayMap?listen");
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
}

void UMultiplayerGameInstance::Join(const FString& IP)
{
	if (!ensure(GetWorld() != nullptr)) return;

	APlayerController* FirstPlayerController = GetFirstLocalPlayerController();
	if (!ensure(FirstPlayerController != nullptr)) return;
	FirstPlayerController->ClientTravel(IP, ETravelType::TRAVEL_Absolute);
	GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Joined"));
}

void UMultiplayerGameInstance::ShowWidget(int32 Number)
{
	switch (Number)
	{
		case 1:
		{
			MenuWidgetRef->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			break;
		}
		case 2:
		{
			JoinWidgetRef->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void UMultiplayerGameInstance::HideWidget()
{
	MenuWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
	JoinWidgetRef->SetVisibility(ESlateVisibility::Collapsed);
}
