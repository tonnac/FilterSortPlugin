// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterElementList.h"

#include "FilterElement.h"
#include "Components/Button.h"
#include "Components/TileView.h"

void UFilterElementList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &UFilterElementList::OnClicked_Button);
	TileView->OnItemClicked().AddUObject(this, &UFilterElementList::OnClicked_FilterElement);
}

void UFilterElementList::NativeConstruct()
{
	Super::NativeConstruct();
	TileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
}

void UFilterElementList::BeginDestroy()
{
	Super::BeginDestroy();
}

void UFilterElementList::SetListItems(const TArray<UFilterElement*>& ElementLists) const
{
	TileView->SetListItems(ElementLists);
}

void UFilterElementList::ScrollToTop() const
{
	TileView->ScrollToTop();
}

void UFilterElementList::OnClicked_Button()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UFilterElementList::OnClicked_FilterElement(UObject* Object) const
{
	if (UFilterElement* FilterElement = Cast<UFilterElement>(Object))
	{
		OnClickedFilterElement.ExecuteIfBound(FilterElement);
	}
}
