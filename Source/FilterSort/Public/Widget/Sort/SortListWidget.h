// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SortContainer.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "SortListWidget.generated.h"

class UListView;
/**
 * 
 */
UCLASS()
class FILTERSORT_API USortListWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

public:
	template <typename T>
	void SetSort(TSortContainer<T>* SortContainer)
	{
		SortContainer->GetUpdateSort().AddUObject(this, &ThisClass::OnUpdateSort);
		ListView->SetListItems(SortContainer->GetSorts());
	}

private:
	void OnUpdateSort();

private:
	UPROPERTY(meta=(BindWidget, EntryClass = SortWidget))
	UListView* ListView = nullptr;
};
