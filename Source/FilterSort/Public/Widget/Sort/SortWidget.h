// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "SortWidget.generated.h"

class UButton;
class USortBase;
class UTextBlock;
class UCheckBox;
/**
 * 
 */
UCLASS()
class FILTERSORT_API USortWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnInitialized() override;
public:
	void SetSort(USortBase* InSortBase);

private:
	UFUNCTION()
	void OnClicked_Button();
	
private:
	UPROPERTY(meta= (BindWidget))
	UCheckBox* CheckBox = nullptr;
	
	UPROPERTY(meta= (BindWidget))
	UTextBlock* TextBlock = nullptr;

	UPROPERTY(meta= (BindWidget))
	UButton* Button = nullptr;
	
private:
	UPROPERTY(EditDefaultsOnly)
	FSlateColor InActiveTextColor;
	
	UPROPERTY(EditDefaultsOnly)
	FSlateColor ActiveTextColor;

private:
	TWeakObjectPtr<USortBase> SortBase;
};
