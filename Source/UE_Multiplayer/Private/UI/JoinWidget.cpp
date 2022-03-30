// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinWidget.h"
#include "Kismet/GameplayStatics.h"
#include <UE_Multiplayer/Public/Game/MultiplayerGameInstance.h>

void UJoinWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Join->OnClicked.AddDynamic(this, &UJoinWidget::OnClickBtnJoin);
}


void UJoinWidget::OnClickBtnJoin()
{
	UMultiplayerGameInstance* GInstance = Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GInstance->Join(Txt_IP->GetText().ToString());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	RemoveFromParent();
}

