// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterBase.h"
#include "FilterElement.h"
#include "Filter/FilterFunctor.h"
#include "Filter.generated.h"

#define IMPLEMENT_ISSATISFIED(TDataType)							\
virtual bool IsSatisfied(const TDataType* _pData) override			\
{																	\
	return IsSatisfied_Private(_pData);								\
}

/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UFilter : public UFilterBase
{
	GENERATED_BODY()
public:
	template <typename T>
	bool IsSatisfied(const T* _pData)
	{
		if (!IsActive())
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
	

	virtual void Initialize() PURE_VIRTUAL(UFilter::Initialize,)
	virtual void ResetFilter();

	virtual void UpdateFilter(UFilterElement* FilterElement) override;
	void EmptyFilter();

	virtual bool IsActive() const override;
	int32 GetFilterNum() const;

	const TArray<UFilterElement*>& GetFilterElements(); 
	
protected:
	UPROPERTY()
	TArray<UFilterElement*> FilterElements;
	TSet<TWeakObjectPtr<UFilterElement>> CurrentFilterElements;	
};