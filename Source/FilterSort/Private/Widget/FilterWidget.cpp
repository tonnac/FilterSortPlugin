// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterWidget.h"

#include "Filter.h"
#include "Widget/FilterElementList.h"

void UFilterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &UFilterWidget::OnClicked);
	FilterElementList->OnClickedFilterElement.BindUObject(this, &UFilterWidget::OnClicked_FilterElement);
}

void UFilterWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UFilter* _Filter = Cast<UFilter>(ListItemObject))
	{
		Filter = _Filter;
		CheckBox->SetCheckedState(Filter->IsEmpty() ? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
		TextBlock->SetText(Filter->GetFilterName());
		SetFilterElements();
	}
}

void UFilterWidget::SetFilterElements()
{
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();

    if (FilterElements.Num() == 1)
    {
    	// Element가 하나인 필터는 ElementList 세팅을 하지않음
    	FilterElementList->SetIsEnabled(false);
    }
    else
    {
    	FilterElementList->SetIsEnabled(true);
    	FilterElementList->SetListItems(Filter->GetFilterElements());
    }
}

void UFilterWidget::OnClicked()
{
	// Filter가 여러 Element를 가지는 경우
	if (FilterElementList->GetIsEnabled() == true)
	{
		FilterElementList->SetVisibility(ESlateVisibility::Visible);
		FilterElementList->ScrollToTop();
	}
	// Filter가 하나의 Element를 가지는 경우
	else
	{
		SimpleDelegate.ExecuteIfBound();
	}
}

void UFilterWidget::OnClicked_FilterElement(UFilterElement* FilterElement) const
{
	if (Filter.IsValid())
	{
		Filter->UpdateFilter(FilterElement);
	}
	
	if (FilterElementList)
	{
		FilterElementList->SetVisibility(ESlateVisibility::Collapsed);
	}
}
