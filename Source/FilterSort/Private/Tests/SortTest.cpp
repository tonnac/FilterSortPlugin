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
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage(), TArray<UClass*> { UTestObjectFooSort::StaticClass() });

	auto& Sorts = SortContainer->GetSorts();
	TWeakObjectPtr<USortBase> FooSort;
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() == UTestObjectFooSort::StaticClass())
		{
			FooSort = *Iter;
			break;
		}
	}

	check(FooSort.IsValid());
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Foo(Objects, true);
	FooSort->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Foo(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBarSort, "Sort.Private.TestObjectBarSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBarSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage(), TArray<UClass*> { UTestObjectBarSort::StaticClass() });

	auto& Sorts = SortContainer->GetSorts();
	TWeakObjectPtr<USortBase> BarSort;
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() == UTestObjectBarSort::StaticClass())
		{
			BarSort = *Iter;
			break;
		}
	}

	check(BarSort.IsValid());
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Bar(Objects, true);
	BarSort->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Bar(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBazSort, "Sort.Private.TestObjectBazSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBazSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage(), TArray<UClass*> { UTestObjectBazSort::StaticClass() });

	auto& Sorts = SortContainer->GetSorts();
	TWeakObjectPtr<USortBase> BazSort;
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() == UTestObjectBazSort::StaticClass())
		{
			BazSort = *Iter;
			break;
		}
	}

	check(BazSort.IsValid());
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Baz(Objects, true);
	BazSort->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Baz(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectQuxSort, "Sort.Private.TestObjectQuxSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectQuxSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage(), TArray<UClass*> { UTestObjectQuxSort::StaticClass() });

	auto& Sorts = SortContainer->GetSorts();
	TWeakObjectPtr<USortBase> QuxSort;
	for (auto Iter = Sorts.CreateIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetClass() == UTestObjectQuxSort::StaticClass())
		{
			QuxSort = *Iter;
			break;
		}
	}

	check(QuxSort.IsValid());
	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	IsValidSortResult_Qux(Objects, true);
	QuxSort->UpdateSort();
	SortContainer->ApplySort(Objects);
	return IsValidSortResult_Qux(Objects, false);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectComplexSort, "Sort.Private.TestObjectComplexSort",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

#define CHECK_COMPLEX_SORT(X)									\
if (PreviousObject->Foo == CurrentObject->Foo)					\
{																\
	if (PreviousObject->Bar == CurrentObject->Bar)				\
	{															\
		if (PreviousObject->Baz == CurrentObject->Baz)			\
		{														\
			check(PreviousObject->Qux ##X CurrentObject->Qux);	\
		}														\
		else													\
		{														\
			check(PreviousObject->Baz ##X CurrentObject->Baz);	\
		}														\
	}															\
	else														\
	{															\
		check(PreviousObject->Bar ##X CurrentObject->Bar);		\
	}															\
}																\
else															\
{																\
	check(PreviousObject->Foo ##X CurrentObject->Foo);			\
}							    

bool TestObjectComplexSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage());

	TArray<UTestObject*> Objects = MakeObjects(50);
	SortContainer->ApplySort(Objects);
	for (int32 i = 1; i < Objects.Num(); ++i)
	{
		const UTestObject* PreviousObject = Objects[i - 1];
		const UTestObject* CurrentObject = Objects[i];
		CHECK_COMPLEX_SORT(>=)
	}
	SortContainer->GetSorts()[0]->UpdateSort();
	SortContainer->ApplySort(Objects);
	for (int32 i = 1; i < Objects.Num(); ++i)
	{
		const UTestObject* PreviousObject = Objects[i - 1];
		const UTestObject* CurrentObject = Objects[i];
		CHECK_COMPLEX_SORT(<=)
	}
	return true;
}
