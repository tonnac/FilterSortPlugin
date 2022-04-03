// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogFilterSort, Log, All)

#define IMPLEMENT_COMMON_PROPERTY(TDataType, Index)											\
private:																					\
	virtual UClass* GetDataTypeClass() const override { return TDataType::StaticClass(); }	\
public:																						\
	virtual int32 GetIndex() const override { return Index; }

class FFilterSortModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TMap<UClass*, TArray<UClass*>> FilterClasses;
	TMap<UClass*, TArray<UClass*>> SortClasses;

private:
	bool GatherFilterClass(UClass* FilterClass, TMap<UClass*, TSet<int32>>& FilterIndices);
	bool GatherSortClass(UClass* SortClass, TMap<UClass*, TSet<int32>>& SortIndices);
};
