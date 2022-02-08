// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterWidget.h"

#include "Filter.h"
#include "Widget/FilterElementList.h"

void UFilterWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UFilter* pFilter = Cast<UFilter>(ListItemObject))
	{
		pFilter->BuildWidget(this);
	}
}

void UFilterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &UFilterWidget::OnClicked);
}

void UFilterWidget::OnClicked()
{
	if (FilterElementList)
	{
		FilterElementList->SetVisibility(ESlateVisibility::Visible);
	}
}
