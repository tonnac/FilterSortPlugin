// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterBase.h"
#include "FilterSortModule.h"
#include "AllFilter.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UAllFilter : public UFilterBase
{
	GENERATED_BODY()

	IMPLEMENT_COMMON_PROPERTY(UObject, 0)
	
public:
	virtual FText GetFilterName() override;
	virtual bool IsActive() const override;

public:
	DECLARE_DELEGATE_RetVal(bool, FIsActiveFilter)
	FIsActiveFilter IsActiveFilter;
};
