// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "SortWidget.generated.h"

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
public:
	void SetSort(USortBase* SortBase) const;

private:
	UPROPERTY(meta= (BindWidget))
	UCheckBox* CheckBox = nullptr;
	
	UPROPERTY(meta= (BindWidget))
	UTextBlock* TextBlock = nullptr;

private:
	UPROPERTY(EditDefaultsOnly)
	FSlateColor InActiveTextColor;
	
	UPROPERTY(EditDefaultsOnly)
	FSlateColor ActiveTextColor;
};
