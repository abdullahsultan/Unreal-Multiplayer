// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class UE_MULTIPLAYER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton* BtnHost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton* BtnJoin;

	UFUNCTION()
	void OnClickHost();

	UFUNCTION()
	void OnClickJoin();
};
