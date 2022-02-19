// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObjectFilter.h"

#include "TestObjectFilterElement.h"

void UFooFilter::Initialize()
{
	for (int32 i = 0; i < 5; ++i)
	{
		UTestObjectFooFilterElement* FilterElement = NewObject<UTestObjectFooFilterElement>(this);
		FilterElement->Initialize(&i);
		FilterElements.Emplace(FilterElement);
	}
}

void UBarFilter::Initialize()
{
	for (int32 i = 0; i < 5; ++i)
	{
		UTestObjectBarFilterElement* FilterElement = NewObject<UTestObjectBarFilterElement>(this);
		FilterElement->Initialize(&i);
		FilterElements.Emplace(FilterElement);
	}
}

void UBazFilter::Initialize()
{
	for (int32 i = 0; i < 5; ++i)
	{
		UTestObjectBazFilterElement* FilterElement = NewObject<UTestObjectBazFilterElement>(this);
		FilterElement->Initialize(&i);
		FilterElements.Emplace(FilterElement);
	}
}

void UQuxFilter::Initialize()
{
	for (int32 i = 0; i < 5; ++i)
	{
		UTestObjectQuxFilterElement* FilterElement = NewObject<UTestObjectQuxFilterElement>(this);
		FilterElement->Initialize(&i);
		FilterElements.Emplace(FilterElement);
	}
}
