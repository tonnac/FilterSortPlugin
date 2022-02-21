// Copyright Epic Games, Inc. All Rights Reserved.

#include "FilterSortModule.h"

#include "AllFilter.h"
#include "Filter.h"

DEFINE_LOG_CATEGORY(LogFilterSort)

#define LOCTEXT_NAMESPACE "FFilterSortModule"

void FFilterSortModule::StartupModule()
{
	for (TObjectIterator<UClass> It; It; ++It)
	{
		const bool bFilterBase = It->GetSuperClass() == UFilter::StaticClass() || It->GetSuperClass() == UAllFilter::StaticClass();
		if (!It->HasAnyClassFlags(EClassFlags::CLASS_Abstract) && bFilterBase)
		{
			auto filterbase = Cast<UFilterBase>(It->GetDefaultObject());
			auto dsds = filterbase->GetDataTypeClass();

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