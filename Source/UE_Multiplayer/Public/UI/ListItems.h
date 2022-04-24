// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "ListItems.generated.h"

/**
 * 
 */
UCLASS()
class UE_MULTIPLAYER_API UListItems : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UEditableText* ServerName_Txt;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UButton* Item_Btn;

	void NativeConstruct() override;

	UFUNCTION()
		void OnItemClick();

	int32 SessionNo;
};
