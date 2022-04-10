// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "TestObjectQuxSort.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UTestObjectQuxSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 3)
	IMPLEMENT_SORT(UTestObject, Qux)
};
