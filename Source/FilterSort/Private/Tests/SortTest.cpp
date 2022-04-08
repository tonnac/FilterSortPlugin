#include "SortContainer.h"
#include "TestHeader.h"
#include "Misc/AutomationTest.h"
#include "TestObject/TestObject.h"
#include "TestObject/Sort/TestObjectBarSort.h"
#include "TestObject/Sort/TestObjectBazSort.h"
#include "TestObject/Sort/TestObjectFooSort.h"
#include "TestObject/Sort/TestObjectQuxSort.h"

#define CHECK_VALID_SORT(Value)																			\
bool IsValidSortResult_##Value(TArray<UTestObject*>& Objects, bool bIsDescending)						\
{																										\
	int32 LatestValue = bIsDescending ? TNumericLimits<int32>::Max() : 0;								\
																										\
	for (const UTestObject* TestObject : Objects)														\
	{																									\
		check(bIsDescending ? LatestValue >= TestObject->Value : LatestValue <= TestObject->Value); 	\
		LatestValue = TestObject->Value;																\
	}																									\
																										\
	return true;																						\
}

CHECK_VALID_SORT(Foo)
CHECK_VALID_SORT(Bar)
CHECK_VALID_SORT(Baz)
CHECK_VALID_SORT(Qux)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectFooSort, "Sort.Private.TestObjectFooSort",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectFooSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage());

	auto& Sorts = SortContainer->GetSorts();
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() != UTestObjectFooSort::StaticClass())
		{
			Iter.RemoveCurrent();
		}
	}
	
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Foo(Objects, true);
	Sorts[0]->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Foo(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBarSort, "Sort.Private.TestObjectBarSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBarSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage());

	auto& Sorts = SortContainer->GetSorts();
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() != UTestObjectBarSort::StaticClass())
		{
			Iter.RemoveCurrent();
		}
	}
	
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Bar(Objects, true);
	Sorts[0]->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Bar(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBazSort, "Sort.Private.TestObjectBazSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBazSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage());

	auto& Sorts = SortContainer->GetSorts();
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() != UTestObjectBazSort::StaticClass())
		{
			Iter.RemoveCurrent();
		}
	}
	
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Baz(Objects, true);
	Sorts[0]->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Baz(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectQuxSort, "Sort.Private.TestObjectQuxSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectQuxSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage());

	auto& Sorts = SortContainer->GetSorts();
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() != UTestObjectQuxSort::StaticClass())
		{
			Iter.RemoveCurrent();
		}
	}
	
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Qux(Objects, true);
	Sorts[0]->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Qux(Objects, false);
}