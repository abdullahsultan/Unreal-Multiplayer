// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE_MultiplayerGameMode.h"
#include "UE_MultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE_MultiplayerGameMode::AUE_MultiplayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
