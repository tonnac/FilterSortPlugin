// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#define ADD_DATATYPE(TDataType)													\
	public:																		\
		virtual bool operator()(const TDataType* _pData)	{ return false;	}

DECLARE_LOG_CATEGORY_EXTERN(LogFilterSort, Log, All)

class FFilterSortModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TMap<UClass*, TArray<UClass*>> classes;
};
