#pragma once
#include "Filter.h"
#include "FilterSortDelegate.h"
#include "FilterInterface.h"
#include "FilterSortModule.h"
#include "GameDelegates.h"

template <typename T>
struct TFilterContainer
{
	TFilterContainer(UObject* Outer)
	{
		FGameDelegates::Get().GetEndPlayMapDelegate().AddRaw(this, &TFilterContainer<T>::Destroy);
		
		if (FFilterSortModule* module = FModuleManager::GetModulePtr<FFilterSortModule>("FilterSort"))
		{
			if (TArray<UClass*>* p = module->classes.Find(T::StaticClass()))
			{
				FOnUpdateFilter aa = FOnUpdateFilter::CreateRaw(this, &TFilterContainer<T>::UpdateFilter);
				for(UClass* c : *p)
				{
					if (UFilter* NewContainer = NewObject<UFilter>(Outer, c))
					{
						NewContainer->Initialize(aa);
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

	void Destroy()
	{
		for (UFilter* Filter : arrr)
		{
			if (Filter->IsRooted())
			{
				Filter->RemoveFromRoot();
			}
		}
		FGameDelegates::Get().GetEndPlayMapDelegate().RemoveAll(this);
	}

	void UpdateFilter(UFilterElement* _pFilterElement)
	{
		const int32 nIndex = _pFilterElement->GetIndex();

		if (arrr.IsValidIndex(nIndex))
		{
			arrr[nIndex]->UpdateFilter(_pFilterElement);
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
