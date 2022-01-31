#pragma once
#include "Filter.h"
#include "FilterInterface.h"
#include "FilterSortModule.h"

template <typename T>
struct TFilterContainer
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
						NewContainer->AddToRoot();
						arrr.Emplace(NewContainer);
					}
				}

				arrr.Sort([](const UFilter& lhs, const UFilter& rhs)
				{
					const int32 lIndex = lhs.GetIndex();
					const int32 rIndex = rhs.GetIndex();
					
					checkf(lIndex != rIndex, TEXT("Index is not equal"));
					
					return lhs.GetIndex() < rhs.GetIndex();					
				});
			}
		}
	}

	void UpdateFilter(TFilterInterface<T>* _pFilterInterface)
	{
		const int32 nIndex = _pFilterInterface->GetIndex();

		if (arrr.IsValidIndex(nIndex))
		{
			arrr[nIndex]->UpdateFilter(_pFilterInterface);
		}

		int32 mn = 53;
	}

	bool operator()(const T* _pData)
	{
		for (int32 i = 0; i < arrr.Num(); ++i)
        {
        	if (arrr[i]->operator()(_pData))
        	{
        		return true;
        	}
        }
        return false;
	}
	
	TArray<UFilter*> arrr;
};
