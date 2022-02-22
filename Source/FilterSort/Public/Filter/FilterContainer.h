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
				for(UClass* c : *p)
				{
					if (UFilterBase* NewFilterBase = NewObject<UFilterBase>(Outer, c))
					{
						if (UFilter* NewFilter = Cast<UFilter>(NewFilterBase))
						{
							NewFilter->Initialize();
						}
						else if (UAllFilter* NewAllFilter = Cast<UAllFilter>(NewFilterBase))
						{
							NewAllFilter->GetIsActive.BindRaw(this, &TFilterContainer<T>::GetIsActiveAllFilter);
						}
						NewFilterBase->OnUpdateFilter.BindRaw(this, &TFilterContainer<T>::UpdateFilter);
						Filters.Emplace(NewFilterBase);	
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
	TSet<T*> ApplyFilter(TArray<T*>& Objects)
	{
		return TSet<T*> {Objects.FilterByPredicate(*this)};
	}

	TSet<T*> ApplyFilter(TArray<const T*>& Objects)
	{
		return TSet<T*> {Objects.FilterByPredicate(*this)};
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
		if (CurrentFilters.Num() == 0)
		{
			return true;
		}
		
		for (const TWeakObjectPtr<UFilter> Filter : CurrentFilters)
		{
			if (Filter->IsSatisfied(_pData))
			{
				return true;
			}			
		}

		for (TWeakObjectPtr<UFilter> Filter : OptionFilters)
        {
        	if (Filter.IsValid() && Filter->IsSatisfied(_pData))
        	{
        		return true;
        	}			
        }
		
        return false;
	}

	FSimpleMulticastDelegate& GetUpdateFilter() { return OnUpdateFilter; }
	const TArray<UFilterBase*>& GetFilters() const { return Filters; }

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
		else
		{
			Empty();
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
	TWeakObjectPtr<UFilter> AllFilter = nullptr;
	TSet<TWeakObjectPtr<UFilter>> CurrentFilters;
	TSet<TWeakObjectPtr<UFilter>> OptionFilters;
	TArray<UFilterBase*> Filters;
	FSimpleMulticastDelegate OnUpdateFilter;
};
