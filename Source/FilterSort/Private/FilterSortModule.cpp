// Copyright Epic Games, Inc. All Rights Reserved.

#include "FilterSortModule.h"
#include "Filter.h"
#include "FilterInterface.h"

DEFINE_LOG_CATEGORY(LogFilterSort)

#define LOCTEXT_NAMESPACE "FFilterSortModule"

void FFilterSortModule::StartupModule()
{
	for (TObjectIterator<UClass> It; It; ++It)
	{
		// if (It->IsChildOf(UFilterInterface::StaticClass()) &&
		// 	!It->HasAnyClassFlags(EClassFlags::CLASS_Abstract))
		// {
		// 	UE_LOG(LogFilterSort, Log, TEXT("Found Class %s"), *It->GetName());
		// }
	}
}

void FFilterSortModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFilterSortModule, FilterSortModule)