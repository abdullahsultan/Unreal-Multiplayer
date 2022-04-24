// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JoinWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UE_Multiplayer/Public/UI/ListItems.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MultiplayerGameInstance.h"


void UJoinWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Join->OnClicked.AddDynamic(this, &UJoinWidget::OnClickBtnJoin);
	GInstance = Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Cast<UMultiplayerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UJoinWidget::OnSessionSearchCompleted);
}


void UJoinWidget::AddServer(FText ServerName, int32 BtnNo)
{
	if (GInstance->WBP_ListItm)
	{
		UListItems* TextBlc = CreateWidget<UListItems>(GetWorld(),GInstance->WBP_ListItm, FName(""));
		TextBlc->ServerName_Txt->SetText(ServerName);
		SessionList->AddChild(TextBlc);
		UE_LOG(LogTemp, Warning, TEXT("CHILDS = %d"), SessionList->GetChildrenCount());
	}
	else
		UE_LOG(LogTemp, Error, TEXT("List Item Null"));
}

void UJoinWidget::OnClickBtnJoin()
{
//	GInstance->Join(Txt_IP->GetText().ToString());
//	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	RemoveFromParent();
}

void UJoinWidget::OnSessionSearchCompleted(bool Success)
{
	int32 SessNo = 0;
	for (const FOnlineSessionSearchResult& SearchResult : GInstance->SessionSearch->SearchResults)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
		AddServer(FText::FromString(SearchResult.GetSessionIdStr()), SessNo);
		SessNo++;
	}
}

