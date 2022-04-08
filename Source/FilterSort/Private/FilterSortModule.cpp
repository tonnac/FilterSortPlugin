// Copyright Epic Games, Inc. All Rights Reserved.

#include "FilterSortModule.h"

#include "AllFilter.h"
#include "Filter.h"
#include "SortBase.h"

DEFINE_LOG_CATEGORY(LogFilterSort)

#define LOCTEXT_NAMESPACE "FFilterSortModule"

void FFilterSortModule::StartupModule()
{
	TMap<UClass*, TSet<int32>> FilterIndices;
	TMap<UClass*, TSet<int32>> SortIndices;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (GatherFilterClass(*It, FilterIndices) == false)
		{
			GatherSortClass(*It, SortIndices);
		}
	}
}

void FFilterSortModule::ShutdownModule()
{
	FilterClasses.Empty(0);
	SortClasses.Empty(0);
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FFilterSortModule::GatherFilterClass(UClass* FilterClass, TMap<UClass*, TSet<int32>>& FilterIndices)
{
	const UClass* SuperClass = FilterClass->GetSuperClass();
	const bool bFilterBase = SuperClass == UFilter::StaticClass() || SuperClass == UAllFilter::StaticClass() || SuperClass == UOptionFilter::StaticClass();
	if (!FilterClass->HasAnyClassFlags(EClassFlags::CLASS_Abstract) && bFilterBase)
	{
		const UFilterBase* FilterBase = Cast<UFilterBase>(FilterClass->GetDefaultObject());
		UClass* DataTypeClass = FilterBase->GetDataTypeClass();
		TSet<int32>& Indices = FilterIndices.FindOrAdd(DataTypeClass);
		checkf(Indices.Contains(FilterBase->GetIndex()) == false, TEXT("%s class index is equal %d"), *DataTypeClass->GetName(), FilterBase->GetIndex());

		Indices.Emplace(FilterBase->GetIndex());

		FilterClasses.FindOrAdd(DataTypeClass).Emplace(FilterClass);
			
		UE_LOG(LogFilterSort, Log, TEXT("Found Filter Class %s"), *FilterClass->GetName());
		return true;
	}
	return false;
}

bool FFilterSortModule::GatherSortClass(UClass* SortClass, TMap<UClass*, TSet<int32>>& SortIndices)
{
	const UClass* SuperClass = SortClass->GetSuperClass();
	const bool bSortBase = SuperClass == USortBase::StaticClass();
	if (!SortClass->HasAnyClassFlags(EClassFlags::CLASS_Abstract) && bSortBase)
	{
		const USortBase* SortBase = Cast<USortBase>(SortClass->GetDefaultObject());
		UClass* DataTypeClass = SortBase->GetDataTypeClass();
		TSet<int32>& Indices = SortIndices.FindOrAdd(DataTypeClass);
		checkf(Indices.Contains(SortBase->GetIndex()) == false, TEXT("%s class index is equal %d"), *DataTypeClass->GetName(), SortBase->GetIndex());

		Indices.Emplace(SortBase->GetIndex());

		SortClasses.FindOrAdd(DataTypeClass).Emplace(SortClass);
			
		UE_LOG(LogFilterSort, Log, TEXT("Found Sort Class %s"), *SortClass->GetName());
		return true;
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFilterSortModule, FilterSortModule)