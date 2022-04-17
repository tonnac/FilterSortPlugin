// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Sort/SortListWidget.h"

#include "Components/ListView.h"

void USortListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ListView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
}

void USortListWidget::OnUpdateSort()
{
	ListView->RegenerateAllEntries();
}
