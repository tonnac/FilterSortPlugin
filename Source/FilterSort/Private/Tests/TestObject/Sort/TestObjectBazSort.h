// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "SortBase.h"
#include "TestObjectBarSort.h"
#include "Tests/TestObject/TestObject.h"
#include "TestObjectBazSort.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UTestObjectBazSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 2)
	
	virtual FText GetSortName() override { return FText::FromString(TEXT("Baz")); }

public:
	IMPLEMENT_SORT(UTestObject, Baz)
};
