// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FilterBase.generated.h"

class UFilterElement;

#define IMPLEMENT_COMMON_FILTER(TDataType, Index)											\
private:																					\
	virtual UClass* GetDataTypeClass() const override { return TDataType::StaticClass(); }	\
public:																						\
	virtual int32 GetIndex() const override { return Index; }

#define ADD_DATATYPE(TDataType)													\
public:																			\
	virtual bool IsSatisfied(const TDataType* _pData) { return false; }

/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UFilterBase : public UObject
{
	GENERATED_BODY()
public:
	virtual FText GetFilterName()  PURE_VIRTUAL(UFilterBase::GetFilterName, return FText::FromString(TEXT("None"));) 
	UFUNCTION()
	virtual UClass* GetDataTypeClass() const PURE_VIRTUAL(UFilterBase::GetDataTypeClass, return nullptr;)
	virtual int32 GetIndex() const PURE_VIRTUAL(UFilterBase::GetIndex, return -1;)
	virtual bool IsActive() const PURE_VIRTUAL(UFilterBase::IsActive, return false;);

	virtual void UpdateFilter(UFilterElement* FilterElement);
	
public:
	DECLARE_DELEGATE_TwoParams(FOnUpdateFilter, UFilterBase*, UFilterElement*)
	FOnUpdateFilter OnUpdateFilter;
};
