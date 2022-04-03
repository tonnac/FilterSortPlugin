// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "SortBase.h"
#include "Tests/TestObject/TestObject.h"
#include "TestObjectBarSort.generated.h"


#define IMPLEMENT_SORT(A, B)\
	virtual ESortResult operator()(const A& lhs, const A& rhs) override \
	{		\
		auto lhsValue = GetValueMacro(lhs, B); \
		auto rhsValue = GetValueMacro(rhs, B); \
		UE_LOG(LogFilterSort, Log, TEXT("Lhs Value : %d, Rhs Value : %d"), lhsValue, rhsValue);	\
		if (lhsValue == rhsValue)\
		{\
			UE_LOG(LogFilterSort, Log, TEXT("\t Equal"));	\
			return ESortResult::Equal;\
		}\
\
		if (lhsValue > rhsValue)	\
		{\
			UE_LOG(LogFilterSort, Log, TEXT("\t Greater"));	\
			return ESortResult::Greater;\
		}\
		else\
		{\
			UE_LOG(LogFilterSort, Log, TEXT("\t Lesser"));	\
			return ESortResult::Lesser;\
		}\
	};

UCLASS()
class FILTERSORT_API UTestObjectBarSort : public USortBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UTestObject, 1)

	virtual FText GetSortName() override { return FText::FromString(TEXT("Bar")); }
	
public:
	IMPLEMENT_SORT(UTestObject, Bar)
};
