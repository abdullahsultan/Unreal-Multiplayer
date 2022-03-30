// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MultiplayerGameInstance.h"

void UMainMenu::NativeConstruct()
{
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::OnClickHost);
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::OnClickJoin);
}

void UMainMenu::OnClickHost()
{
	Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->Host();
	RemoveFromParent();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
}

void UMainMenu::OnClickJoin()
{
	UMultiplayerGameInstance* GInstance = Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GInstance->JWidget)
	{
		UUserWidget* Menu = CreateWidget<UUserWidget>(this, GInstance->JWidget);
		if (Menu)
		{
			Menu->AddToViewport();
		}
	}
	RemoveFromParent();
}