// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "SetServerNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE_MULTIPLAYER_API USetServerNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

	UFUNCTION()
		void OnEnterClicked();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(BindWidget))
	UEditableText* TxtBoxServerName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UEditableText* TxtBoxNoOfPlayers;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* BtnEnter;
	
};
