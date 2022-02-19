// Fill out your copyright notice in the Description page of Project Settings.


#include "Filter.h"

void UFilter::UpdateFilter(UFilterElement* _pFilterElement)
{
	if (CurrentFilters.Contains(_pFilterElement))
	{
		CurrentFilters.Remove(_pFilterElement);
		_pFilterElement->oo.bActive = false;
	}
	else
	{
		CurrentFilters.Emplace(_pFilterElement);
		_pFilterElement->oo.bActive = true;
	}
		
	OnUpdateFilter.ExecuteIfBound(this, _pFilterElement);
}

void UFilter::EmptyFilter()
{
	for (auto Iter = CurrentFilters.CreateIterator(); Iter; ++Iter)
	{
		if (Iter->IsValid())
		{
			Iter->Get()->oo.bActive = false;
		}
		Iter.RemoveCurrent();
	}
	OnUpdateFilter.ExecuteIfBound(this, nullptr);
}

bool UFilter::IsEmpty() const
{
	return CurrentFilters.Num() == 0;
}

int32 UFilter::GetFilterNum() const
{
	return FilterElements.Num();
}

const TArray<UFilterElement*>& UFilter::GetFilterElements()
{
	return FilterElements;
}
