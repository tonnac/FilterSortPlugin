// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "SortBase.h"
#include "TestObjectBarSort.h"
#include "TestObjectFooSort.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UTestObjectFooSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 0)
public:
	IMPLEMENT_SORT(UTestObject, GetFoo())
};
