#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SortBase.generated.h"

class UAObject;
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
class UTestObject;
#endif //!(UE_BUILD_SHIPPING || UE_BUILD_TEST)

enum class ESortResult : uint8
{
	Equal,
	Lesser,
	Greater
};

#define GET_VALUE_MACRO(A, B) A.##B

#define ADD_SORT_DATATYPE(TDataType)																			\
public:																											\
	virtual ESortResult operator()(const TDataType& lhs, const TDataType& rhs) { return ESortResult::Equal; }

#define IMPLEMENT_SORT(TDataType, Value)												\
virtual ESortResult operator()(const TDataType& lhs, const TDataType& rhs) override		\
{																						\
	auto lhsValue = GET_VALUE_MACRO(lhs, Value);										\
	auto rhsValue = GET_VALUE_MACRO(rhs, Value);										\
	if (lhsValue == rhsValue)															\
	{																					\
		return ESortResult::Equal;														\
	}																					\
	return lhsValue > rhsValue ? ESortResult::Greater : ESortResult::Lesser;			\
};

UCLASS(Abstract)
class FILTERSORT_API USortBase : public UObject
{
	GENERATED_BODY()

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	ADD_SORT_DATATYPE(UTestObject)
#endif //!(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	ADD_SORT_DATATYPE(UAObject)

public:
	virtual UClass* GetDataTypeClass() const PURE_VIRTUAL(USortBase::GetDataTypeClass, return nullptr;)
	virtual FText GetSortName() PURE_VIRTUAL(USortBase::GetSortName, return FText::GetEmpty();)
	virtual int32 GetIndex() const PURE_VIRTUAL(USortBase::GetIndex, return -1;)
	virtual bool IsActive() const PURE_VIRTUAL(USortBase::IsActive, return false;)

	void UpdateSort();

public:
	DECLARE_DELEGATE_OneParam(FOnUpdateSort, USortBase*)
	FOnUpdateSort OnUpdateSort;
};
