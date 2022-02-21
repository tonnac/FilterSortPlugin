// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterContainer.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "FilterListWidget.generated.h"

class UListView;

/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterListWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
public:	
	template <typename T>
	void SetFilter(TFilterContainer<T>* FilterContainer)
	{
		FilterContainer->GetUpdateFilter().AddUObject(this, &UFilterListWidget::OnUpdateFilter);
		ListView->SetListItems(FilterContainer->GetFilters());
	}

private:
	void OnUpdateFilter() const;
	
private:
	UPROPERTY(meta=(BindWidget, EntryClass = FilterWidget))
	UListView* ListView = nullptr;
};
