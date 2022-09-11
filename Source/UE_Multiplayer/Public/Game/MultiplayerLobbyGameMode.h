// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UE_MultiplayerGameMode.h"
#include "MultiplayerLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE_MULTIPLAYER_API AMultiplayerLobbyGameMode : public AUE_MultiplayerGameMode
{
	GENERATED_BODY()

public:

	void PostLogin(APlayerController* NewPlaer) override;

	void Logout(AController* LeftPlayer) override;

	int32 NumberofPlayers = 0;
	
};
