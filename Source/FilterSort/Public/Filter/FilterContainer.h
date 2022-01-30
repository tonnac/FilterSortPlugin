#pragma once
#include "Filter.h"
#include "FilterInterface.h"
#include "FilterSortModule.h"

template <typename T>
struct TFilterContainer : TFilterInterface<T>
{
	TFilterContainer(UObject* Outer)
	{
		if (FFilterSortModule* module = FModuleManager::GetModulePtr<FFilterSortModule>("FilterSort"))
		{
			if (TArray<UClass*>* p = module->classes.Find(T::StaticClass()))
			{
				for(UClass* c : *p)
				{
					if (UFilter* NewContainer = NewObject<UFilter>(Outer, c))
					{
						NewContainer->Initialize();
						arrr.Emplace(NewContainer);
					}
				}
			}
		}
	}

	virtual bool Is_Satisfied(const T* Data) override
	{
		for (int32 i = 0; i < arrr.Num(); ++i)
		{
			if ((*arrr[i])(Data))
			{
				return true;
			}
		}
		return false;
	}
	UPROPERTY()
	TArray<UFilter*> arrr;
};
