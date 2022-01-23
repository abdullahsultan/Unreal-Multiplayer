// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"
#include "Engine/World.h"

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