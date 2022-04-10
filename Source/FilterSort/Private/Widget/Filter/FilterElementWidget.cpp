// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Filter/FilterElementWidget.h"

#include "FilterElement.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UFilterElementWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UFilterElement* FilterElement = Cast<UFilterElement>(ListItemObject))
	{
		if (FilterElement->FilterElementProperty.ElementTexture != nullptr)
		{
			WidgetSwitcher->SetActiveWidgetIndex(ImageIndex);
			Image->SetBrushFromTexture(FilterElement->FilterElementProperty.ElementTexture);
		}
		else
		{
			WidgetSwitcher->SetActiveWidgetIndex(TextIndex);
			Text->SetText(FilterElement->FilterElementProperty.ElementName);
		}
		ActiveImage->SetColorAndOpacity(FilterElement->FilterElementProperty.bActive.Get() ? ActiveColor : InActiveColor);
	}
}

void UFilterElementWidget::BeginDestroy()
{
	Super::BeginDestroy();
}
