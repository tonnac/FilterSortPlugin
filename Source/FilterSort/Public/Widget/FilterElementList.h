// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FilterElementList.generated.h"

class UButton;
class UTileView;
/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterElementList : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnClicked_Button();
	
public:
	UPROPERTY(meta=(BindWidget, EntryClass = FilterElementWidget))
	UTileView* TileView = nullptr;

private:
	UPROPERTY(meta=(BindWidget))
	UButton* Button = nullptr;
};
