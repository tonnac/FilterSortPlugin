#pragma once
#include "AllFilter.h"
#include "Filter.h"
#include "FilterSortModule.h"

template <typename TDataType>
class TFilterContainer : public FGCObject
{
public:
	TFilterContainer(UObject* Outer)
	{
		if (FFilterSortModule* FilterSortModule = FModuleManager::GetModulePtr<FFilterSortModule>("FilterSort"))
		{
			if (TArray<UClass*>* Classes = FilterSortModule->FilterClasses.Find(TDataType::StaticClass()))
			{
				if (UAllFilter* NewAllFilter = NewObject<UAllFilter>(Outer, UAllFilter::StaticClass()))
				{
					NewAllFilter->IsActiveFilter.BindRaw(this, &TFilterContainer<TDataType>::IsActiveAllFilter);
					NewAllFilter->OnUpdateFilter.BindRaw(this, &TFilterContainer<TDataType>::UpdateFilter);
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
							NewFilterBase->OnUpdateFilter.BindRaw(this, &TFilterContainer<TDataType>::UpdateOptionFilter);
						}
						else
						{
							Filters.Emplace(NewFilterBase);
							NewFilterBase->OnUpdateFilter.BindRaw(this, &TFilterContainer<TDataType>::UpdateFilter);
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
	void ApplyFilter(TArray<TDataType*>& Objects)
	{
		Objects.RemoveAll(*this);
	}

	void ApplyFilter(TArray<const TDataType*>& Objects)
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
	
	bool operator()(const TDataType* Data) const
	{
		if (CurrentFilters.Num() == 0 && CurrentOptionFilters.Num() == 0)
		{
			return false;
		}
		
		for (const TWeakObjectPtr<UFilter> Filter : CurrentFilters)
		{
			if (Filter.IsValid() && Filter->IsSatisfied(Data))
			{
				return false;
			}			
		}

		for (const TWeakObjectPtr<UFilter> Filter : CurrentOptionFilters)
        {
        	if (Filter.IsValid() && Filter->IsSatisfied(Data))
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
		if (UpdateFilter_Private(CurrentFilters, FilterBase, FilterElement) == false)
		{
			// All Filter Click
			Empty();
		}
		OnUpdateFilter.Broadcast();
	}

	void UpdateOptionFilter(UFilterBase* FilterBase, UFilterElement* FilterElement)
	{
		UpdateFilter_Private(CurrentOptionFilters, FilterBase, FilterElement);
		OnUpdateFilter.Broadcast();
	}

	bool UpdateFilter_Private(TSet<TWeakObjectPtr<UFilter>>& FilterSet, UFilterBase* FilterBase, UFilterElement* FilterElement) const
	{
		if (UFilter* Filter = Cast<UFilter>(FilterBase))
		{
			if (FilterSet.Contains(Filter) && !Filter->IsActive())
			{
				FilterSet.Remove(Filter);
				return true;
			}
			if (!FilterSet.Contains(Filter) && Filter->IsActive())
			{
				FilterSet.Emplace(Filter);
				return true;
			}
		}
		return false;
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
