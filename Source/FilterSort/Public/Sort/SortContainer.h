#pragma once
#include "FilterSortModule.h"
#include "SortBase.h"

template <typename T>
class TSortContainer : public FGCObject
{
public:
	TSortContainer(UObject* Outer)
	{
		if (FFilterSortModule* FilterSortModule = FModuleManager::GetModulePtr<FFilterSortModule>("FilterSort"))
		{
			if (TArray<UClass*>* Classes = FilterSortModule->SortClasses.Find(T::StaticClass()))
			{
				for (const UClass* FilterClass : *Classes)
				{
					if (USortBase* NewSortBase = NewObject<USortBase>(Outer, FilterClass))
					{
						Sorts.Emplace(NewSortBase);
					}
				}
			}
		}

		Sorts.Sort([](const USortBase& lhs, const USortBase& rhs)
		{
			return lhs.GetIndex() < rhs.GetIndex();
		});
	}

	void ApplySort(TArray<T*>& Objects)
	{
		Objects.Sort(*this);
	}

	void ApplySort(TArray<const T*>& Objects)
	{
		Objects.Sort(*this);
	}

	bool operator()(const T& lhs, const T& rhs) const
	{
		for (USortBase* SortBase : OptionSorts)
		{
			const ESortResult SortResult = (*SortBase)(lhs, rhs);

			if (SortResult != ESortResult::Equal)
			{
				if (bIsDescending)
				{
					return SortResult == ESortResult::Greater;
				}
				else
				{
					return SortResult == ESortResult::Lesser;
				}	
			}
		}
		
		for (USortBase* SortBase : Sorts)
		{
			const ESortResult SortResult = (*SortBase)(lhs, rhs);

			if (SortResult != ESortResult::Equal)
			{
				if (bIsDescending)
				{
					return SortResult == ESortResult::Greater;
				}
				else
				{
					return SortResult == ESortResult::Lesser;
				}	
			}
		}
		return false;
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(Sorts);
		Collector.AddReferencedObjects(OptionSorts);
	}

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	TArray<USortBase*>& GetSorts() { return Sorts; }
	TArray<USortBase*>& GetOptionSorts() { return OptionSorts; }
#else
	const TArray<USortBase*>& GetSorts() const { return Sorts; }
	const TArray<USortBase*>& GetOptionSorts() const { return OptionSorts; }
#endif
	
private:
	TArray<USortBase*> Sorts;
	TArray<USortBase*> OptionSorts;
	bool bIsDescending = false;
};
