#pragma once
#include "AllFilter.h"
#include "Filter.h"
#include "FilterSortModule.h"

template <typename T>
class TFilterContainer : public FGCObject
{
public:
	TFilterContainer(UObject* Outer)
	{
		if (FFilterSortModule* FilterSortModule = FModuleManager::GetModulePtr<FFilterSortModule>("FilterSort"))
		{
			if (TArray<UClass*>* Classes = FilterSortModule->FilterClasses.Find(T::StaticClass()))
			{
				if (UAllFilter* NewAllFilter = NewObject<UAllFilter>(Outer, UAllFilter::StaticClass()))
				{
					NewAllFilter->IsActiveFilter.BindRaw(this, &TFilterContainer<T>::IsActiveAllFilter);
					NewAllFilter->OnUpdateFilter.BindRaw(this, &TFilterContainer<T>::UpdateFilter);
					Filters.Emplace(NewAllFilter);
				}
				
				for (const UClass* FilterClass : *Classes)
				{
					if (UFilterBase* NewFilterBase = NewObject<UFilterBase>(Outer, FilterClass))
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

	bool IsActiveAllFilter() const
	{
		return CurrentFilters.Num() == 0;
	}
	
	/** FGCObject implementation */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(Filters);
		Collector.AddReferencedObjects(OptionFilters);
	}

private:
	TSet<TWeakObjectPtr<UFilter>> CurrentFilters;
	TSet<TWeakObjectPtr<UFilter>> CurrentOptionFilters;
	TArray<UFilterBase*> OptionFilters;
	TArray<UFilterBase*> Filters;
	FSimpleMulticastDelegate OnUpdateFilter;
};
