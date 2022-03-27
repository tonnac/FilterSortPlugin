#pragma once
#include <algorithm>

#include "AllFilter.h"
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
				if (UAllFilter* NewAllFilter = NewObject<UAllFilter>(Outer, UAllFilter::StaticClass()))
				{
					NewAllFilter->GetIsActive.BindRaw(this, &TFilterContainer<T>::GetIsActiveAllFilter);
					NewAllFilter->OnUpdateFilter.BindRaw(this, &TFilterContainer<T>::UpdateFilter);
					Filters.Emplace(NewAllFilter);
				}
				
				for (UClass* c : *p)
				{
					if (UFilterBase* NewFilterBase = NewObject<UFilterBase>(Outer, c))
					{
						NewFilterBase->Initialize();
						if (UOptionFilter* NewOptionFilter = Cast<UOptionFilter>(NewFilterBase))
						{
							OptionFilters.Emplace(NewOptionFilter);
							NewFilterBase->OnUpdateFilter.BindRaw(this, &TFilterContainer<T>::UpdateOptionFilter);
						}
						else
						{
							Filters.Emplace(NewFilterBase);
							NewFilterBase->OnUpdateFilter.BindRaw(this, &TFilterContainer<T>::UpdateFilter);
						}
					}
				}

				Filters.Sort([](const UFilterBase& lhs, const UFilterBase& rhs)
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

	void Empty()
	{
		for (const TWeakObjectPtr<UFilter> CurrentFilter : CurrentFilters)
		{
			CurrentFilter->ResetFilter();
		}
		CurrentFilters.Empty();
	}
	
	bool operator()(const T* _pData) const
	{
		if (CurrentFilters.Num() == 0 && CurrentOptionFilters.Num() == 0)
		{
			return false;
		}
		
		for (const TWeakObjectPtr<UFilter> Filter : CurrentFilters)
		{
			if (Filter.IsValid() && Filter->IsSatisfied(_pData))
			{
				return false;
			}			
		}

		for (const TWeakObjectPtr<UFilter> Filter : CurrentOptionFilters)
        {
        	if (Filter.IsValid() && Filter->IsSatisfied(_pData))
        	{
        		return false;
        	}			
        }
		
        return true;
	}

	FSimpleMulticastDelegate& GetUpdateFilter() { return OnUpdateFilter; }
	const TArray<UFilterBase*>& GetFilters() const { return Filters; }
	const TArray<UFilterBase*>& GetOptionFilters() const { return OptionFilters; }

private:
	void UpdateFilter(UFilterBase* FilterBase, UFilterElement* FilterElement)
	{
		if (UFilter* Filter = Cast<UFilter>(FilterBase))
		{
			if (CurrentFilters.Contains(Filter) && !Filter->IsActive())
			{
				CurrentFilters.Remove(Filter);
			}
			else if (!CurrentFilters.Contains(Filter) && Filter->IsActive())
			{
				CurrentFilters.Emplace(Filter);
			}
		}
		// All Filter Click
		else
		{
			Empty();
		}
	
		OnUpdateFilter.Broadcast();
	}

	void UpdateOptionFilter(UFilterBase* FilterBase, UFilterElement* FilterElement)
	{
		if (UFilter* Filter = Cast<UFilter>(FilterBase))
		{
			if (CurrentOptionFilters.Contains(Filter) && !Filter->IsActive())
			{
				CurrentOptionFilters.Remove(Filter);
			}
			else if (!CurrentOptionFilters.Contains(Filter) && Filter->IsActive())
			{
				CurrentOptionFilters.Emplace(Filter);
			}
		}
	
		OnUpdateFilter.Broadcast();
	}

	bool GetIsActiveAllFilter() const
	{
		return CurrentFilters.Num() == 0;
	}
	
	/** FGCObject implementation */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(Filters);
	}

private:
	TSet<TWeakObjectPtr<UFilter>> CurrentFilters;
	TSet<TWeakObjectPtr<UFilter>> CurrentOptionFilters;
	TArray<UFilterBase*> OptionFilters;
	TArray<UFilterBase*> Filters;
	FSimpleMulticastDelegate OnUpdateFilter;
};
