// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "FilterWidget.generated.h"

class UFilterBase;
class UFilterElement;
class UFilter;
class UButton;
class UFilterElementList;
class UTextBlock;
class UCheckBox;
/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	void SetFilterElements(UFilter* Filter);
	
private:
	UFUNCTION()
	void OnClicked();
	void OnClicked_FilterElement(UFilterElement* FilterElement, UFilter* Filter) const;
	
public:
	UPROPERTY(meta=(BindWidget))
	UCheckBox* CheckBox = nullptr;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* Button = nullptr;

	UPROPERTY(meta=(BindWidget))
	UFilterElementList* FilterElementList = nullptr;

private:
	TWeakObjectPtr<UFilterBase> FilterBase = nullptr;
};
