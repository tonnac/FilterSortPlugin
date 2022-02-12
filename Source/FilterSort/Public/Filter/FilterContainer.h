#pragma once
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
		for (int32 i = 0; i < Filters.Num(); ++i)
        {
        	if (Filters[i]->operator()(_pData))
        	{
        		return true;
        	}
        }
        return false;
	}

	FSimpleMulticastDelegate& GetUpdateFilter() { return OnUpdateFilter; }
	const TArray<UFilter*>& GetFilters() const { return Filters; }

private:
	void UpdateFilter(UFilter* _pFilter, UFilterElement* _pFilterElement) const
	{
		OnUpdateFilter.Broadcast();
	}
	
	/** FGCObject implementation */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(Filters);
	}

private:
	TArray<UFilter*> Filters;
	FSimpleMulticastDelegate OnUpdateFilter;
};
