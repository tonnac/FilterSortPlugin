// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Filter.generated.h"

class UAObject;
/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UFilter : public UObject
{
	GENERATED_BODY()

public:
	virtual bool operator()(const UAObject* _pData)
	{
		
		
		return false;
	}
};
