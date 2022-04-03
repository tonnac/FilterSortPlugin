#include "SortContainer.h"
#include "TestHeader.h"
#include "Misc/AutomationTest.h"
#include "TestObject/TestObject.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectSort, "Sort.Private.TestObjectSort",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObjectSort::RunTest(const FString& Parameters)
{
	const TUniquePtr<TSortContainer<UTestObject>> SortContainer = MakeUnique<TSortContainer<UTestObject>>(GetTransientPackage());

	TArray<USortBase*>& Sorts = SortContainer->GetSorts();
	Sorts.RemoveAt(1);
	Sorts.RemoveAt(1);
	Sorts.RemoveAt(1);
	
	TArray<UTestObject*> Objects = MakeObjects(50);
	TArray<UTestObject*> ObjectsCopy = Objects;

	SortContainer->ApplySort(Objects);

	int32 mn = 53;
	
	// Make the test pass by returning true, or fail by returning false.
	return true;
}
