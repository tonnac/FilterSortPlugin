// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "FilterElementWidget.generated.h"

class UTextBlock;
class UImage;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterElementWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	static constexpr int32 ImageIndex = 0;
	static constexpr int32 TextIndex = 1;
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher = nullptr;

	UPROPERTY(meta=(BindWidget))
	UImage* Image = nullptr;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text = nullptr;
};
