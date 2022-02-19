// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FilterElement.h"
#include "Filter/FilterFunctor.h"
#include "Filter.generated.h"


#define IMPLEMENT_COMMON_FILTER(TDataType, Index)																	\
private:																													\
	virtual UClass* GetDataTypeClass() const override { return TDataType::StaticClass(); }									\
public:																														\
	virtual int32 GetIndex() const override { return Index; }

class UAObject;
/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UFilter : public UObject
{
	GENERATED_BODY()
public:
	virtual FText GetFilterName() PURE_VIRTUAL(UFilter::GetFilterName, return FText::GetEmpty(););
	
	virtual void Initialize() PURE_VIRTUAL(UFilter::Initialize, )
	UFUNCTION()
	virtual UClass* GetDataTypeClass() const PURE_VIRTUAL(UFilter::GetDataTypeClass, return nullptr;);
	virtual int32 GetIndex() const PURE_VIRTUAL(UFilter::GetIndex, return -1;);

public:
	template <typename T>
	bool IsSatisfied(const T* _pData)
	{
		if (IsEmpty())
		{
			return false;
		}

		for (const TWeakObjectPtr<UFilterElement>& FilterElement : CurrentFilterElements)
		{
			if (FilterElement.IsValid() && FilterElement->IsSatisfied(_pData))
			{
				return true;
			}
		}

		return false;
	}
	
	void UpdateFilter(UFilterElement* _pFilterElement);
	void EmptyFilter();
	
	bool IsEmpty() const;
	int32 GetFilterNum() const;

	const TArray<UFilterElement*>& GetFilterElements(); 
	
public:
	DECLARE_DELEGATE_TwoParams(FOnUpdateFilter, UFilter*, UFilterElement*)
	FOnUpdateFilter OnUpdateFilter;

protected:
	UPROPERTY()
	TArray<UFilterElement*> FilterElements;
	TSet<TWeakObjectPtr<UFilterElement>> CurrentFilterElements;	
};