#include "TestObject.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FilterTest, "Private.Tests.FilterTest",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FilterTest::RunTest(const FString& Parameters)
{
	UTestObject* TestObject = NewObject<UTestObject>();

	TestEqual(TEXT("Simple Test"), TestObject->A, 0);
	// Make the test pass by returning true, or fail by returning false.
	return true;
}
