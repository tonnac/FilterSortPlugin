// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterBase.h"
#include "AllFilter.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UAllFilter : public UFilterBase
{
	GENERATED_BODY()
	
public:
	virtual FText GetFilterName() override;
	virtual bool IsActive() const override;

public:
	DECLARE_DELEGATE_RetVal(bool, FGetIsActive)
	FGetIsActive GetIsActive;
};
