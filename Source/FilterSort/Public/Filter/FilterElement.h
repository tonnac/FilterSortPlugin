// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "UObject/Object.h"
#include "FilterElement.generated.h"

class UAObject;

struct FOOO
{
	FText KK;
	UTexture2D* pp = nullptr;
};

/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterElement : public UObject
{
	GENERATED_BODY()

public:
	ADD_DATATYPE(UAObject)
	
public:
	virtual void Initialize(void* Src) PURE_VIRTUAL(UFilterElement::Initialize, );
	
public:
	FOOO oo;
};
