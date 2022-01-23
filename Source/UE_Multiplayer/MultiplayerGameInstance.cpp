// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGameInstance.h"
#include "Engine/World.h"

void UMultiplayerGameInstance::Host()
{
	if (!ensure(GetWorld() != nullptr))
		GetEngine()->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("GetWorld IS NULL"));

		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}