// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterElement.h"
#include "TestObjectFilterElement.generated.h"

class UTestObject;
UCLASS()
class UTestObjectFooFilterElement : public UFilterElement
{
	GENERATED_BODY()
public:
	virtual void Initialize(void* Src) override;
	virtual bool operator()(const UTestObject* TestObject) override;
	
private:
	int32 Foo = 0;
};

UCLASS()
class UTestObjectBarFilterElement : public UFilterElement
{
	GENERATED_BODY()
public:
	virtual void Initialize(void* Src) override;
	virtual bool operator()(const UTestObject* TestObject) override;

private:
	int32 Bar = 0;
};

UCLASS()
class UTestObjectBazFilterElement : public UFilterElement
{
	GENERATED_BODY()
public:
	virtual void Initialize(void* Src) override;
	virtual bool operator()(const UTestObject* TestObject) override;

private:
	int32 Baz = 0;
};

UCLASS()
class UTestObjectQuxFilterElement : public UFilterElement
{
	GENERATED_BODY()
public:
	virtual void Initialize(void* Src) override;
	virtual bool operator()(const UTestObject* TestObject) override;

private:
	int32 Qux = 0;
};
