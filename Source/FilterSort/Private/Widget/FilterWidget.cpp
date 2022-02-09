// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterWidget.h"

#include "Filter.h"
#include "Widget/FilterElementList.h"

void UFilterWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UFilter* _pFilter = Cast<UFilter>(ListItemObject))
	{
		pFilter = _pFilter;
		pFilter->BuildWidget(this);
	}
}

void UFilterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &UFilterWidget::OnClicked);
	FilterElementList->TileView->OnItemClicked().AddUObject(this, &UFilterWidget::OnClicked_FilterElement);
}

void UFilterWidget::OnClicked()
{
	if (FilterElementList)
	{
		FilterElementList->SetVisibility(ESlateVisibility::Visible);
	}
}

void UFilterWidget::OnClicked_FilterElement(UObject* _pObject)
{
	if (UFilterElement* pFilterElement = Cast<UFilterElement>(_pObject))
	{
		pFilter->OnUpdateFilter.ExecuteIfBound(pFilterElement);
	}
}
