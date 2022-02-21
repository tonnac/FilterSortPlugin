// Fill out your copyright notice in the Description page of Project Settings.


#include "Filter.h"

void UFilter::UpdateFilter(UFilterElement* FilterElement)
{
	if (CurrentFilterElements.Contains(FilterElement))
	{
		CurrentFilterElements.Remove(FilterElement);
		FilterElement->oo.bActive = false;
	}
	else
	{
		CurrentFilterElements.Emplace(FilterElement);
		FilterElement->oo.bActive = true;
	}

	Super::UpdateFilter(FilterElement);
}

void UFilter::EmptyFilter()
{
	ResetFilter();
	OnUpdateFilter.ExecuteIfBound(this, nullptr);
}

void UFilter::ResetFilter()
{
	for (auto Iter = CurrentFilterElements.CreateIterator(); Iter; ++Iter)
	{
		if (Iter->IsValid())
		{
			Iter->Get()->oo.bActive = false;
		}
	}
	CurrentFilterElements.Empty();
}

bool UFilter::IsActive() const
{
	return CurrentFilterElements.Num() != 0;
}

int32 UFilter::GetFilterNum() const
{
	return FilterElements.Num();
}

const TArray<UFilterElement*>& UFilter::GetFilterElements()
{
	return FilterElements;
}
