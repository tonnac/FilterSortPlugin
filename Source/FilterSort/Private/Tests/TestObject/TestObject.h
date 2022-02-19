// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TestObject.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UTestObject : public UObject
{
	GENERATED_BODY()

public:
	void Initialize()
	{
		Foo = FMath::RandRange(0, 4);
		Bar = FMath::RandRange(0, 4);
		Baz = FMath::RandRange(0, 4);
		Qux = FMath::RandRange(0, 4);
	}

public:
	int32 Foo = 0;
	int32 Bar = 0;
	int32 Baz = 0;
	int32 Qux = 0;
};
