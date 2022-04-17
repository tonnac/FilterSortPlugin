// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Sort/SortWidget.h"

#include "SortBase.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void USortWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	if (USortBase* SortBase = Cast<USortBase>(ListItemObject))
	{
		SetSort(SortBase);
	}
}

void USortWidget::SetSort(USortBase* SortBase) const
{
	TextBlock->SetText(SortBase->GetSortName());
	if (SortBase->IsActive())
	{
		TextBlock->SetColorAndOpacity(ActiveTextColor);
		CheckBox->SetCheckedState(SortBase->IsDescending.Execute() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}
	else
	{
		TextBlock->SetColorAndOpacity( InActiveTextColor);
		CheckBox->SetCheckedState(ECheckBoxState::Undetermined);
	}
}
