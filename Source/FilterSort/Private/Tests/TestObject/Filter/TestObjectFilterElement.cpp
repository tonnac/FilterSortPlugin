﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TestObjectFilterElement.h"

#include "Tests/TestObject/TestObject.h"

void UTestObjectFooFilterElement::Initialize(void* Src)
{
	Foo = *static_cast<int32*>(Src);
}

bool UTestObjectFooFilterElement::operator()(const UTestObject* TestObject)
{
	return TestObject->Foo == Foo;
}

void UTestObjectBarFilterElement::Initialize(void* Src)
{
	Bar = *static_cast<int32*>(Src);
}

bool UTestObjectBarFilterElement::operator()(const UTestObject* TestObject)
{
	return TestObject->Bar == Bar;
}

void UTestObjectBazFilterElement::Initialize(void* Src)
{
	Baz = *static_cast<int32*>(Src);
}

bool UTestObjectBazFilterElement::operator()(const UTestObject* TestObject)
{
	return TestObject->Baz == Baz;
}

void UTestObjectQuxFilterElement::Initialize(void* Src)
{
	Qux = *static_cast<int32*>(Src);
}

bool UTestObjectQuxFilterElement::operator()(const UTestObject* TestObject)
{
	return TestObject->Qux == Qux;
}
