// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SetServerNameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MultiplayerGameInstance.h"
#include "Kismet/KismetStringLibrary.h"



void USetServerNameWidget::NativeConstruct()
{
	BtnEnter->OnClicked.AddDynamic(this, &USetServerNameWidget::OnEnterClicked);
}

void USetServerNameWidget::OnEnterClicked()
{
	Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->ServerNameToHost = TxtBoxServerName->GetText().ToString();
	Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->Host();
	Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->NumberofPlayers = UKismetStringLibrary::Conv_StringToInt(TxtBoxNoOfPlayers->GetText().ToString());
}
