// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ListItems.h"
#include "UE_Multiplayer/Public/Game/MultiplayerGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UListItems::NativeConstruct()
{
	Item_Btn->OnClicked.AddDynamic(this, &UListItems::OnItemClick);
}

void UListItems::OnItemClick()
{
	Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->Join(ServerName_Txt->GetText().ToString(), SessionNo);
}
