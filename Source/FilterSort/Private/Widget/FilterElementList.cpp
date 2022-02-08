// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FilterElementList.h"

#include "Components/Button.h"
#include "Components/TileView.h"

void UFilterElementList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddUniqueDynamic(this, &UFilterElementList::OnClicked_Button);
}

void UFilterElementList::NativeConstruct()
{
	Super::NativeConstruct();
	TileView->SetScrollbarVisibility(ESlateVisibility::Collapsed);
}

void UFilterElementList::OnClicked_Button()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
