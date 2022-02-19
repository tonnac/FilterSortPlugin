// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterElementWidget.h"

#include "FilterElement.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UFilterElementWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UFilterElement* FilterElement = Cast<UFilterElement>(ListItemObject))
	{
		if (FilterElement->oo.pp != nullptr)
		{
			WidgetSwitcher->SetActiveWidgetIndex(ImageIndex);
			Image->SetBrushFromTexture(FilterElement->oo.pp);
		}
		else
		{
			WidgetSwitcher->SetActiveWidgetIndex(TextIndex);
			Text->SetText(FilterElement->oo.KK);
		}
		ActiveImage->SetColorAndOpacity(FilterElement->oo.bActive ? ActiveColor : InActiveColor);
	}
}

void UFilterElementWidget::BeginDestroy()
{
	Super::BeginDestroy();
}
