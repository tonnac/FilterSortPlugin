// Copyright Epic Games, Inc. All Rights Reserved.

#include "FilterSortModule.h"

#include "AllFilter.h"
#include "Filter.h"

DEFINE_LOG_CATEGORY(LogFilterSort)

#define LOCTEXT_NAMESPACE "FFilterSortModule"

void FFilterSortModule::StartupModule()
{
	TMap<UClass*, TSet<int32>> FilterIndices;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		const UClass* SuperClass = It->GetSuperClass();
		const bool bFilterBase = SuperClass == UFilter::StaticClass() || SuperClass == UAllFilter::StaticClass() || SuperClass == UOptionFilter::StaticClass();
		if (!It->HasAnyClassFlags(EClassFlags::CLASS_Abstract) && bFilterBase)
		{
			UFilterBase* FilterBase = Cast<UFilterBase>(It->GetDefaultObject());
			UClass* FilterClass = FilterBase->GetDataTypeClass();
			TSet<int32>& Indices = FilterIndices.FindOrAdd(FilterClass);
			checkf(Indices.Contains(FilterBase->GetIndex()) == false, TEXT("%s class index is equal %d"), *FilterClass->GetName(), FilterBase->GetIndex());

			Indices.Emplace(FilterBase->GetIndex());

			FilterClasses.FindOrAdd(FilterClass).Emplace(*It);
			
			UE_LOG(LogFilterSort, Log, TEXT("Found Class %s"), *It->GetName());
		}
	}
}

void FFilterSortModule::ShutdownModule()
{
	FilterClasses.Empty(0);
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFilterSortModule, FilterSortModule)