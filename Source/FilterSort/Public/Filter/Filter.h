// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "FilterBase.h"
#include "FilterElement.h"
#include "Filter.generated.h"

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
	

	virtual void Initialize() override;
	virtual void ResetFilter();

	virtual void UpdateFilter(UFilterElement* FilterElement) override;
	void EmptyFilter();

	virtual bool IsActive() const override;
	int32 GetFilterNum() const;

	const TArray<UFilterElement*>& GetFilterElements();

private:
	bool IsActiveAllElement() const;
	
protected:
	UPROPERTY()
	TArray<UFilterElement*> FilterElements;
	TSet<TWeakObjectPtr<UFilterElement>> CurrentFilterElements;	
};

UCLASS(Abstract)
class FILTERSORT_API UOptionFilter : public UFilter
{
	GENERATED_BODY()
};