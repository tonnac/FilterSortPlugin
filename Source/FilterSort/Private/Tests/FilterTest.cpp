
#include "FilterContainer.h"
#include "TestHeader.h"
#include "TestObject/TestObject.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectFooFilter, "Filter.Private.TestObjectFooFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectFooFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);
	TArray<UTestObject*> ObjectsCopy = Objects;

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Foo]++;
	}

	auto Filters = FilterContainer->GetFilters();
	UFilter* Filter = Cast<UFilter>(Filters[1]);
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();

	for (int32 i = 0; i < 5; ++i)
	{
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);
		
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Values[i]);

		Filter->UpdateFilter(FilterElement);
		ObjectsCopy = Objects;
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Objects.Num());	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBarFilter, "Filter.Private.TestObjectBarFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBarFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);
	TArray<UTestObject*> ObjectsCopy = Objects;

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Bar]++;
	}

	auto Filters = FilterContainer->GetFilters();
	UFilter* Filter = Cast<UFilter>(Filters[2]);
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();
	
	for (int32 i = 0; i < 5; ++i)
	{
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);
		
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Values[i]);

		Filter->UpdateFilter(FilterElement);
		ObjectsCopy = Objects;
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Objects.Num());	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectBazFilter, "Filter.Private.TestObjectBazFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectBazFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);
	TArray<UTestObject*> ObjectsCopy = Objects;

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Baz]++;
	}

	auto Filters = FilterContainer->GetFilters();
	UFilter* Filter = Cast<UFilter>(Filters[3]);
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();
	
	for (int32 i = 0; i < 5; ++i)
	{
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);

		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Values[i]);

		Filter->UpdateFilter(FilterElement);
		ObjectsCopy = Objects;
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Objects.Num());	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectQuxFilter, "Filter.Private.TestObjectQuxFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectQuxFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);
	TArray<UTestObject*> ObjectsCopy = Objects;

	TStaticArray<int32, 5> Values = MakeUniformStaticArray<int32, 5>(0);
	for (const UTestObject* Object : Objects)
	{
		Values[Object->Qux]++;
	}

	auto Filters = FilterContainer->GetFilters();
	UFilter* Filter = Cast<UFilter>(Filters[4]);
	TArray<UFilterElement*> FilterElements = Filter->GetFilterElements();
	
	for (int32 i = 0; i < 5; ++i)
	{
		UFilterElement* FilterElement = FilterElements[i];
		Filter->UpdateFilter(FilterElement);
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Values[i]);

		Filter->UpdateFilter(FilterElement);
		ObjectsCopy = Objects;
		FilterContainer->ApplyFilter(ObjectsCopy);

		TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Objects.Num());	
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectCombinationFilter, "Filter.Private.TestObjectCombinationFilter",
								 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectCombinationFilter::RunTest(const FString& Parameters)
{
	const TUniquePtr<TFilterContainer<UTestObject>> FilterContainer = MakeUnique<TFilterContainer<UTestObject>>(GetTransientPackage());
	TArray<UTestObject*> Objects = MakeObjects(500);
	TArray<UTestObject*> ObjectsCopy = Objects;

	constexpr int32 TargetFooValue = 2;
	constexpr int32 TargetBarValue = 1;
	constexpr int32 TargetBazValue = 3;
	constexpr int32 TargetQuxValue = 4;
	
	TArray<int32> TargetValues = { TargetFooValue, TargetBarValue, TargetBazValue, TargetQuxValue };

	int32 FilteredObjectNumber = 0;
	
	for (const UTestObject* Object : Objects)
	{
		if (Object->Foo == TargetFooValue ||
			Object->Bar == TargetBarValue ||
			Object->Baz == TargetBazValue ||
			Object->Qux == TargetQuxValue)
		{
			FilteredObjectNumber++;
		}
	}

	auto UpdateFilter = [FilterContainer = FilterContainer.Get(), TargetValues]()
	{
		for (int32 i = 1; i < 5; ++i)
		{
			UFilter* Filter = Cast<UFilter>(FilterContainer->GetFilters()[i]);
			UFilterElement* FilterElement = Filter->GetFilterElements()[TargetValues[i - 1]];
			Filter->UpdateFilter(FilterElement);
		}
	};

	UpdateFilter();
	FilterContainer->ApplyFilter(ObjectsCopy);

	TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), FilteredObjectNumber);

	UpdateFilter();
	ObjectsCopy = Objects;
	FilterContainer->ApplyFilter(ObjectsCopy);

	TestEqual(TEXT("Filter Result"), ObjectsCopy.Num(), Objects.Num());	
	
	return true;
}