
#include "FilterContainer.h"
#include "TestObject/TestObject.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectFooFilter, "Filter.Private.TestObjectFooFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

TArray<UTestObject*> MakeObjects(int32 Number)
{
	TArray<UTestObject*> Objects;

	for (int32 i = 0; i < Number; ++i)
	{
		if (UTestObject* Object = NewObject<UTestObject>())
		{
			Object->Initialize();
			Objects.Emplace(Object);
		}
	}	

	return Objects;
}

bool TestObjectFooFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Foo]++;
	}

	TArray<UFilter*> Filters = FilterContainer->GetFilters();
	UFilter* Filter = Filters[0];
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();

	for (int32 i = 0; i < 5; ++i)
	{
		auto Copy = Objects;
		auto Copy1 = Objects;
		
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);

		const int32 OriginNum = Copy.Num();
		FilterContainer->ApplyFilter(Copy);

		TestEqual(TEXT("Filter Result"), Copy.Num(), OriginNum - Values[i]);

		Filter->UpdateFilter(FilterElement);
		FilterContainer->ApplyFilter(Copy1);

		TestEqual(TEXT("Filter Result"), Copy1.Num(), OriginNum);	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBarFilter, "Filter.Private.TestObjectBarFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBarFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Bar]++;
	}

	TArray<UFilter*> Filters = FilterContainer->GetFilters();
	UFilter* Filter = Filters[1];
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();
	
	for (int32 i = 0; i < 5; ++i)
	{
		auto Copy = Objects;
		auto Copy1 = Objects;
		
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);

		const int32 OriginNum = Copy.Num();
		FilterContainer->ApplyFilter(Copy);

		TestEqual(TEXT("Filter Result"), Copy.Num(), OriginNum - Values[i]);

		Filter->UpdateFilter(FilterElement);
		FilterContainer->ApplyFilter(Copy1);

		TestEqual(TEXT("Filter Result"), Copy1.Num(), OriginNum);	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBazFilter, "Filter.Private.TestObjectBazFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBazFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Baz]++;
	}

	TArray<UFilter*> Filters = FilterContainer->GetFilters();
	UFilter* Filter = Filters[2];
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();
	
	for (int32 i = 0; i < 5; ++i)
	{
		auto Copy = Objects;
		auto Copy1 = Objects;
		
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);

		const int32 OriginNum = Copy.Num();
		FilterContainer->ApplyFilter(Copy);

		TestEqual(TEXT("Filter Result"), Copy.Num(), OriginNum - Values[i]);

		Filter->UpdateFilter(FilterElement);
		FilterContainer->ApplyFilter(Copy1);

		TestEqual(TEXT("Filter Result"), Copy1.Num(), OriginNum);	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectQuxFilter, "Filter.Private.TestObjectQuxFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectQuxFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Qux]++;
	}

	TArray<UFilter*> Filters = FilterContainer->GetFilters();
	UFilter* Filter = Filters[3];
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();
	
	for (int32 i = 0; i < 5; ++i)
	{
		auto Copy = Objects;
		auto Copy1 = Objects;
		
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);

		const int32 OriginNum = Copy.Num();
		FilterContainer->ApplyFilter(Copy);

		TestEqual(TEXT("Filter Result"), Copy.Num(), OriginNum - Values[i]);

		Filter->UpdateFilter(FilterElement);
		FilterContainer->ApplyFilter(Copy1);

		TestEqual(TEXT("Filter Result"), Copy1.Num(), OriginNum);	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectCombinationFilter, "Filter.Private.TestObjectCombinationFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectCombinationFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);

	constexpr int32 TargetFooValue = 2;
	constexpr int32 TargetBarValue = 1;
	constexpr int32 TargetBazValue = 3;
	constexpr int32 TargetQuxValue = 4;

	TArray<int32> TargetValues = { TargetFooValue, TargetBarValue, TargetBazValue, TargetQuxValue };

	int32 NotFilteredObjectNumber = 0;
	
	for (const UTestObject* Object : Objects)
	{
		if (Object->Foo != TargetFooValue &&
			Object->Bar != TargetBarValue &&
			Object->Baz != TargetBazValue &&
			Object->Qux != TargetQuxValue)
		{
			NotFilteredObjectNumber++;
		}
	}

	auto UpdateFilter = [FilterContainer = FilterContainer.Get(), TargetValues]()
	{
		for (int32 i = 0; i < 4; ++i)
		{
			UFilter* Filter = FilterContainer->GetFilters()[i];
			UFilterElement* FilterElement = Filter->GetFilterElements()[TargetValues[i]];
			Filter->UpdateFilter(FilterElement);
		}
	};
	
	auto Copy = Objects;
	auto Copy1 = Objects;

	UpdateFilter();
	FilterContainer->ApplyFilter(Copy);

	TestEqual(TEXT("Filter Result"), Copy.Num(), NotFilteredObjectNumber);

	UpdateFilter();
	FilterContainer->ApplyFilter(Copy1);

	TestEqual(TEXT("Filter Result"), Copy1.Num(), Objects.Num());	
	
	return true;
}