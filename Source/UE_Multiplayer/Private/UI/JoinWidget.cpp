// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UE_Multiplayer/Public/Game/MultiplayerGameInstance.h"
#include "UE_Multiplayer/Public/UI/ListItems.h"
#include "Kismet/GameplayStatics.h"


void UJoinWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Join->OnClicked.AddDynamic(this, &UJoinWidget::OnClickBtnJoin);
}


void UJoinWidget::AddServer(FText ServerName)
{
	if (Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->WBP_ListItm)
	{
		SessionList->ClearChildren();
		UListItems* TextBlc = CreateWidget<UListItems>(GetWorld(), 
			Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->WBP_ListItm, FName(""));
		TextBlc->ServerName_Txt->SetText(ServerName);
		UE_LOG(LogTemp, Error, TEXT("NUNUNU %s"), *TextBlc->ServerName_Txt->GetText().ToString());
		SessionList->AddChild(TextBlc);
		UE_LOG(LogTemp, Warning, TEXT("CHILDS = %d"), SessionList->GetChildrenCount());
	}
	else
		UE_LOG(LogTemp, Error, TEXT("List Item Null"));
}

void UJoinWidget::OnClickBtnJoin()
{
	AddServer(FText::FromString("TEST"));
	UMultiplayerGameInstance* GInstance = Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GInstance->Join(Txt_IP->GetText().ToString());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	//RemoveFromParent();
}

