// Fill out your copyright notice in the Description page of Project Settings.


#include "Filter.h"

#include "FilterAllElement.h"

void UFilter::UpdateFilter(UFilterElement* FilterElement)
{
	if (UFilterAllElement* AllElement = Cast<UFilterAllElement>(FilterElement))
	{
		EmptyFilter();
	}
	else
	{
		if (CurrentFilterElements.Contains(FilterElement))
		{
			CurrentFilterElements.Remove(FilterElement);
			FilterElement->FilterElementProperty.bActive = false;
		}
		else
		{
			CurrentFilterElements.Emplace(FilterElement);
			FilterElement->FilterElementProperty.bActive = true;
		}
	}
	Super::UpdateFilter(FilterElement);
}

void UFilter::EmptyFilter()
{
	ResetFilter();
	OnUpdateFilter.ExecuteIfBound(this, nullptr);
}

void UFilter::Initialize()
{
	UFilterAllElement* AllElement = NewObject<UFilterAllElement>(this);
	if (IsValid(AllElement))
	{
		AllElement->FilterElementProperty.ElementName = FText::FromString(TEXT("All"));
		AllElement->FilterElementProperty.bActive.BindUObject(this, &UFilter::IsActiveAllElement);
		FilterElements.Emplace(AllElement);
	}
}

void UFilter::ResetFilter()
{
	for (auto Iter = CurrentFilterElements.CreateIterator(); Iter; ++Iter)
	{
		if (Iter->IsValid())
		{
			Iter->Get()->FilterElementProperty.bActive = false;
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

bool UFilter::IsActiveAllElement() const
{
	return !IsActive();
}
