#pragma once
#include "TestObject/TestObject.h"

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
