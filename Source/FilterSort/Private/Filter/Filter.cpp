// Fill out your copyright notice in the Description page of Project Settings.


#include "Filter.h"

void UFilter::UpdateFilter(UFilterElement* _pFilterElement)
{
	if (CurrentFilterElements.Contains(_pFilterElement))
	{
		CurrentFilterElements.Remove(_pFilterElement);
		_pFilterElement->oo.bActive = false;
	}
	else
	{
		CurrentFilterElements.Emplace(_pFilterElement);
		_pFilterElement->oo.bActive = true;
	}
		
	OnUpdateFilter.ExecuteIfBound(this, _pFilterElement);
}

void UFilter::EmptyFilter()
{
	for (auto Iter = CurrentFilterElements.CreateIterator(); Iter; ++Iter)
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
	return CurrentFilterElements.Num() == 0;
}

int32 UFilter::GetFilterNum() const
{
	return FilterElements.Num();
}

const TArray<UFilterElement*>& UFilter::GetFilterElements()
{
	return FilterElements;
}
