// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FilterElementList.generated.h"

class UFilterElement;
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

	virtual void BeginDestroy() override;
	
public:
	void SetListItems(const TArray<UFilterElement*>& ElementLists) const;
	void ScrollToTop() const;
	
private:
	UFUNCTION()
	void OnClicked_Button();
	void OnClicked_FilterElement(UObject* Object) const;

public:
	DECLARE_DELEGATE_OneParam(FOnClickedFilterElement, UFilterElement*)
	FOnClickedFilterElement OnClickedFilterElement;
	
private:
	UPROPERTY(meta=(BindWidget, EntryClass = FilterElementWidget))
	UTileView* TileView = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button = nullptr;
};
