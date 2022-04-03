// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterBase.h"
#include "FilterElement.generated.h"

class UAObject;
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
class UTestObject;
#endif

struct FFilterElementProperty
{
	FText ElementName;
	UTexture2D* ElementTexture = nullptr;
	TAttribute<bool> bActive = false;
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
	ADD_FILTER_DATATYPE(UTestObject)
#endif
	ADD_FILTER_DATATYPE(UAObject)

	virtual void BeginDestroy() override;
	
public:
	virtual void Initialize(void* Src) PURE_VIRTUAL(UFilterElement::Initialize, );
	
public:
	FFilterElementProperty FilterElementProperty;
};
