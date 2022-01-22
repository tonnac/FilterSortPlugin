// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FilterSortFunctor.h"
#include "FilterElementContainer.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterElementContainer : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() {}
	virtual bool IsEmpty() { return true; }

protected:
	template <typename T, typename U>
	bool Is_Satisfied_Internal(T* _pElementContainer, const U* _pDataType)
	{
		return TFilterContainerFunctor<T>()(_pElementContainer, _pDataType);
	}
};