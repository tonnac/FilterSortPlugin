// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "UObject/Object.h"
#include "FilterElement.generated.h"

class UAObject;
class UTestObject;

struct FOOO
{
	FText KK;
	UTexture2D* pp = nullptr;
	bool bActive = false;
};

/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterElement : public UObject
{
	GENERATED_BODY()

public:
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	ADD_DATATYPE(UTestObject)
#endif
	ADD_DATATYPE(UAObject)

	virtual void BeginDestroy() override;
	
public:
	virtual void Initialize(void* Src) PURE_VIRTUAL(UFilterElement::Initialize, );
	
public:
	FOOO oo;
};
