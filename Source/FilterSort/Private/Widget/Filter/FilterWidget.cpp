// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Filter/FilterWidget.h"

#include "Filter.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Widget/Filter/FilterElementList.h"

void UFilterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &UFilterWidget::OnClicked);
}

void UFilterWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UFilterBase* _FilterBase = Cast<UFilterBase>(ListItemObject))
	{
		FilterBase = _FilterBase;
		if (UFilter* _Filter = Cast<UFilter>(_FilterBase))
		{
			Button->SetIsEnabled(_Filter->GetFilterNum() != 0);
			SetFilterElements(_Filter);
		}
		// All Filter
		else
		{
			FilterElementList->SetIsEnabled(false);
			Button->SetIsEnabled(true);
		}
		CheckBox->SetCheckedState(_FilterBase->IsActive() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
		TextBlock->SetText(_FilterBase->GetFilterName());

		if (UOptionFilter* OptionFilter = Cast<UOptionFilter>(_FilterBase))
		{
			TextBlock->SetColorAndOpacity(FLinearColor::Blue);
		}
	}
}

void UFilterWidget::SetFilterElements(UFilter* Filter)
{
	const TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();

    if (FilterElements.Num() == 1)
    {
    	// Element가 하나인 필터는 ElementList 세팅을 하지않음
    	FilterElementList->SetIsEnabled(false);
    }
    else
    {
    	FilterElementList->SetIsEnabled(true);
    	FilterElementList->SetListItems(Filter->GetFilterElements());
    	FilterElementList->OnClickedFilterElement.BindUObject(this, &UFilterWidget::OnClicked_FilterElement, Filter);
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
		if (FilterBase.IsValid())
		{
			if (UFilter* Filter = Cast<UFilter>(FilterBase))
			{
				Filter->UpdateFilter(Filter->GetFilterElements()[0]);
			}
			else
			{
				FilterBase->UpdateFilter(nullptr);
			}
		}
	}
}

void UFilterWidget::OnClicked_FilterElement(UFilterElement* FilterElement, UFilter* Filter) const
{
	if (IsValid(Filter))
	{
		Filter->UpdateFilter(FilterElement);
	}
	
	if (FilterElementList)
	{
		FilterElementList->SetVisibility(ESlateVisibility::Collapsed);
	}
}
