// Copyright Epic Games, Inc. All Rights Reserved.

#include "FilterSortModule.h"
#include "Filter.h"

DEFINE_LOG_CATEGORY(LogFilterSort)

#define LOCTEXT_NAMESPACE "FFilterSortModule"

void FFilterSortModule::StartupModule()
{
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (!It->HasAnyClassFlags(EClassFlags::CLASS_Abstract) && It->GetSuperClass() == UFilter::StaticClass())
		{
			auto defulat = Cast<UFilter>(It->GetDefaultObject());
			auto dsds = defulat->GetDataTypeClass();

			classes.FindOrAdd(dsds).Emplace(*It);
			
			UE_LOG(LogFilterSort, Log, TEXT("Found Class %s"), *It->GetName());
		}
	}
}

void FFilterSortModule::ShutdownModule()
{
	classes.Empty(0);
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFilterSortModule, FilterSortModule)