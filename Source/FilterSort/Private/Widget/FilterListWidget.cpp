// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterListWidget.h"

void UFilterListWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);


	TAttribute<bool> b = BIND_UOBJECT_ATTRIBUTE(bool, BB);
	
}

void UFilterListWidget::OnUpdateFilter() const
{
	ListView->RegenerateAllEntries();
}
