// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Sort/SortWidget.h"

#include "SortBase.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void USortWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	if (USortBase* InSortBase = Cast<USortBase>(ListItemObject))
	{
		SetSort(InSortBase);
	}
}

void USortWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &ThisClass::OnClicked_Button);
}

void USortWidget::SetSort(USortBase* InSortBase) 
{
	SortBase = InSortBase;
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

void USortWidget::OnClicked_Button()
{
	SortBase->UpdateSort();
}
