// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "SortBase.h"
#include "Tests/TestObject/TestObject.h"
#include "TestObjectBarSort.generated.h"

UCLASS()
class FILTERSORT_API UTestObjectBarSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 1)
public:
	IMPLEMENT_SORT(UTestObject, Bar)
};
