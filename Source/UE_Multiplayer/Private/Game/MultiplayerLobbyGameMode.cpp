// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MultiplayerLobbyGameMode.h"
#include "Game/MultiplayerGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AMultiplayerLobbyGameMode::PostLogin(APlayerController* NewPlaer)
{
	Super::PostLogin(NewPlaer);
	NumberofPlayers++;

	if (NumberofPlayers >= Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->NumberofPlayers)
	{
		Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->StartSession();
		bUseSeamlessTravel = true;
		GetWorld()->ServerTravel("/Game/Levels/PlayMap");
	}

}

void AMultiplayerLobbyGameMode::Logout(AController* LeftPlayer)
{
	Super::Logout(LeftPlayer);
	NumberofPlayers--;
}

