// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "TestObjectBarSort.generated.h"

UCLASS()
class FILTERSORT_API UTestObjectBarSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 1)
	IMPLEMENT_SORT(UTestObject, Bar)
};
