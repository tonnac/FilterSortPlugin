// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "SortBase.h"
#include "TestObjectBarSort.h"
#include "TestObjectQuxSort.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UTestObjectQuxSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 3)
	
virtual FText GetSortName() override { return FText::FromString(TEXT("Qux")); }

public:
	IMPLEMENT_SORT(UTestObject, Qux)
};
