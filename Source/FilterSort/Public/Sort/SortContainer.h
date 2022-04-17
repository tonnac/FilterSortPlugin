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
						NewSortBase->OnUpdateSort.BindRaw(this, &TSortContainer<T>::UpdateSort);
						NewSortBase->IsDescending.BindRaw(this, &TSortContainer<T>::IsDescending);
						Sorts.Emplace(NewSortBase);
					}
				}
			}
		}

		Sorts.Sort([](const USortBase& lhs, const USortBase& rhs)
		{
			return lhs.GetIndex() < rhs.GetIndex();
		});

		for (USortBase* Sort : Sorts)
		{
			DefaultSorts.Emplace(Sort);
		}
		CurrentSorts = DefaultSorts;
	}

	void ApplySort(TArray<T*>& Objects)
	{
		Objects.Sort(*this);
	}

	void ApplySort(TArray<const T*>& Objects)
	{
		Objects.Sort(*this);
	}

	TOptional<bool> SortImplementation(const TArray<USortBase*>& SortElements, const T& lhs,
	                                   const T& rhs) const
	{
		for (USortBase* SortBase : SortElements)
		{
			const ESortResult SortResult = (*SortBase)(lhs, rhs);

			if (SortResult != ESortResult::Equal)
			{
				return bIsDescending ? SortResult == ESortResult::Greater : SortResult == ESortResult::Lesser;
			}
		}
		return TOptional<bool>{};
	};

	bool operator()(const T& lhs, const T& rhs) const
	{
		if (TOptional<bool> bResult = SortImplementation(CurrentOptionSorts, lhs, rhs))
		{
			return bResult.GetValue();
		}

		if (TOptional<bool> bResult = SortImplementation(CurrentSorts, lhs, rhs))
		{
			return bResult.GetValue();
		}

		return false;
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		Collector.AddReferencedObjects(Sorts);
		Collector.AddReferencedObjects(OptionSorts);
	}

	FSimpleMulticastDelegate& GetUpdateSort() const { return OnUpdateSort; }

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	TArray<USortBase*>& GetSorts() { return CurrentSorts; }
	TArray<USortBase*>& GetOptionSorts() { return OptionSorts; }
#else
	const TArray<USortBase*>& GetSorts() const { return Sorts; }
	const TArray<USortBase*>& GetOptionSorts() const { return OptionSorts; }
#endif

private:
	void UpdateSort(USortBase* SortBase)
	{
		const int32 Index = CurrentSorts.IndexOfByKey(SortBase);
		if (Index == 0)
		{
			bIsDescending = !bIsDescending;
		}
		else
		{
			CurrentSorts = DefaultSorts;
			if (Index == INDEX_NONE)
			{
				CurrentSorts.Insert(SortBase, 0);
				bIsDescending = true;
			}
			else
			{
				const int32 NewIndex = CurrentSorts.IndexOfByKey(SortBase);
				if (NewIndex != 0)
				{
					CurrentSorts.Swap(0, NewIndex);
				}
			}
		}
		OnUpdateSort.Broadcast();
	}

	bool IsDescending() const
	{
		return bIsDescending;
	}


private:
	mutable FSimpleMulticastDelegate OnUpdateSort;
	
	TArray<USortBase*> DefaultSorts;
	TArray<USortBase*> CurrentSorts;
	TArray<USortBase*> CurrentOptionSorts;

	TArray<USortBase*> Sorts;
	TArray<USortBase*> OptionSorts;
	bool bIsDescending = true;
};
