// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterElementList.h"

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
	TArray<UObject*> ListItems = TileView->GetListItems();

	bool bEqualListItems = true;

	if (ListItems.Num() != ElementLists.Num())
	{
		bEqualListItems = false;
	}
	else
	{
		for (int32 i = 0; i < ListItems.Num(); ++i)
		{
			if (ListItems[i] != ElementLists[i])
			{
				bEqualListItems = false;
				break;
			}
		} 
	}

	if (bEqualListItems)
	{
		TileView->RegenerateAllEntries();
	}
	else
	{
		TileView->SetListItems(ElementLists);
	}
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
