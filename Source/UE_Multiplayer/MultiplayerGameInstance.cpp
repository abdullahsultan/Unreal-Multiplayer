// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"
#include "Engine/World.h"


UMultiplayerGameInstance::UMultiplayerGameInstance() 
{
	ConstructorHelpers::FClassFinder<UUserWidget>MenuWidget(TEXT("/Game/MenuWidget"));
	if (MenuWidget.Class)
	{
		MWidget = MenuWidget.Class;
	}
}

void UMultiplayerGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Class: %s"), *MWidget->GetName());
}

void UMultiplayerGameInstance::Host()
{
	if (!ensure(GetWorld() != nullptr)) return;

	GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
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

void UMultiplayerGameInstance::LoadMenu()
{
	if (MWidget)
	{
		UUserWidget* Menu = CreateWidget<UUserWidget>(this, MWidget);
		if (Menu)
		{
			Menu->AddToViewport();
		}
	}
}
