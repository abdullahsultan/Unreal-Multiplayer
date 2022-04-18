// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "JoinWidget.generated.h"

class UMultiplayerGameInstance;
/**
 * 
 */
UCLASS()
class UE_MULTIPLAYER_API UJoinWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton* Btn_Join;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UEditableText* Txt_IP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UScrollBox* SessionList;

	UFUNCTION()
		void AddServer(FText ServerName);

	UFUNCTION()
	void OnClickBtnJoin();

	UFUNCTION()
		void OnSessionSearchCompleted(bool Success);

	UPROPERTY()
	UMultiplayerGameInstance* GInstance;
};
