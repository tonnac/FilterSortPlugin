#pragma once
#include <algorithm>

#include "Filter.h"
#include "FilterSortModule.h"

template <typename T>
struct TFilterContainer : public FGCObject
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
						NewContainer->OnUpdateFilter.BindRaw(this, &TFilterContainer<T>::UpdateFilter);
						Filters.Emplace(NewContainer);
					}
				}

				Filters.Sort([](const UFilter& lhs, const UFilter& rhs)
				{
					const int32 lIndex = lhs.GetIndex();
					const int32 rIndex = rhs.GetIndex();
					
					checkf(lIndex != rIndex, TEXT("Index is not equal"));
					
					return lhs.GetIndex() < rhs.GetIndex();					
				});
			}
		}
	}

public:
	void ApplyFilter(TArray<T*>& Objects)
	{
		Objects.RemoveAll(*this);
	}

	void ApplyFilter(TArray<const T*>& Objects)
	{
		Objects.RemoveAll(*this);
	}
	
	bool operator()(const T* _pData) const
	{
		if (CurrentFilters.Num() == 0)
		{
			return false;
		}
		
		for (TWeakObjectPtr<UFilter> Filter : CurrentFilters)
		{
			if (Filter.IsValid() && Filter->IsSatisfied(_pData))
			{
				return false;
			}			
		}
		
        return true;
	}

	FSimpleMulticastDelegate& GetUpdateFilter() { return OnUpdateFilter; }
	const TArray<UFilter*>& GetFilters() const { return Filters; }

private:
	void UpdateFilter(UFilter* Filter, UFilterElement* FilterElement)
	{
		if (CurrentFilters.Contains(Filter) && Filter->IsEmpty())
		{
			CurrentFilters.Remove(Filter);
		}
		else if (!CurrentFilters.Contains(Filter) && !Filter->IsEmpty())
		{
			CurrentFilters.Emplace(Filter);
		}
	
		OnUpdateFilter.Broadcast();
	}
	
	/** FGCObject implementation */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(Filters);
	}

private:
	TSet<TWeakObjectPtr<UFilter>> CurrentFilters;
	TArray<UFilter*> Filters;
	FSimpleMulticastDelegate OnUpdateFilter;
};
