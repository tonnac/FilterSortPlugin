// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Filter.h"
#include "Tests/TestObject/TestObject.h"
#include "TestObjectFilter.generated.h"

/**
 * 
 */
UCLASS()
class UFooFilter : public UFilter
{
	GENERATED_BODY()
	IMPLEMENT_COMMON_FILTER(UTestObject, 1)

public:
	virtual void Initialize() override;
};

UCLASS()
class UBarFilter : public UFilter
{
	GENERATED_BODY()
	IMPLEMENT_COMMON_FILTER(UTestObject, 2)

public:
	virtual void Initialize() override;
};

UCLASS()
class UBazFilter : public UFilter
{
	GENERATED_BODY()
	IMPLEMENT_COMMON_FILTER(UTestObject, 3)

public:
	virtual void Initialize() override;
};

UCLASS()
class UQuxFilter : public UFilter
{
	GENERATED_BODY()
	IMPLEMENT_COMMON_FILTER(UTestObject, 4)

public:
	virtual void Initialize() override;
};