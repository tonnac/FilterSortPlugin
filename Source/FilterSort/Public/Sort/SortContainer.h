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
				for (const UClass* SortClass : *Classes)
				{
					if (USortBase* NewSortBase = NewObject<USortBase>(Outer, SortClass))
					{
						NewSortBase->OnUpdateSort.BindRaw(this, &TSortContainer<T>::UpdateSort);
						NewSortBase->IsDescending.BindRaw(this, &TSortContainer<T>::IsDescending);
						NewSortBase->IsActiveEvent.BindRaw(this, &TSortContainer<T>::IsActiveSort);
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

		if (PrioritySort.IsValid() == false)
		{
			UpdateSort(DefaultSorts[1].Get());
		}
	}

	void ApplySort(TArray<T*>& Objects)
	{
		Objects.Sort(*this);
	}

	void ApplySort(TArray<const T*>& Objects)
	{
		Objects.Sort(*this);
	}

	TOptional<bool> SortImplementation(const TArray<TWeakObjectPtr<USortBase>>& SortElements, const T& lhs,
	                                   const T& rhs) const
	{
		for (TWeakObjectPtr<USortBase> SortBase : SortElements)
		{
			if (SortBase.IsValid())
			{
				const ESortResult SortResult = (*SortBase)(lhs, rhs);

				if (SortResult != ESortResult::Equal)
				{
					return bIsDescending ? SortResult == ESortResult::Greater : SortResult == ESortResult::Lesser;
				}
			}
		}
		return TOptional<bool>{};
	};

	bool operator()(const T& lhs, const T& rhs) const
	{
		const ESortResult SortResult = (*PrioritySort)(lhs, rhs);
		if (SortResult != ESortResult::Equal)
		{
			return bIsDescending ? SortResult == ESortResult::Greater : SortResult == ESortResult::Lesser;
		}
		
		if (TOptional<bool> bResult = SortImplementation(CurrentOptionSorts, lhs, rhs))
		{
			return bResult.GetValue();
		}

		if (TOptional<bool> bResult = SortImplementation(DefaultSorts, lhs, rhs))
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
	TArray<USortBase*>& GetSorts() { return Sorts; }
	TArray<USortBase*>& GetOptionSorts() { return OptionSorts; }
#else
	const TArray<USortBase*>& GetSorts() const { return Sorts; }
	const TArray<USortBase*>& GetOptionSorts() const { return OptionSorts; }
#endif

private:
	void UpdateSort(USortBase* SortBase)
	{
		if (SortBase == PrioritySort)
		{
			bIsDescending = !bIsDescending;
		}
		else
		{
			for (int32 i = 0; i < DefaultSorts.Num(); ++i)
			{
				TWeakObjectPtr<USortBase>& Sort = DefaultSorts[i];
				if (Sort.IsValid() == false)
				{
					Sort = PrioritySort.Get();
				}
				else if (Sort == SortBase)
				{
					Sort = nullptr;
				}
			}

			PrioritySort = SortBase;
			bIsDescending = true;
		}
		
		OnUpdateSort.Broadcast();
	}
	
	bool IsDescending() const
	{
		return bIsDescending;
	}

	bool IsActiveSort(const USortBase* SortBase) const
	{
		check(PrioritySort.IsValid());
		return PrioritySort == SortBase;
	}

private:
	mutable FSimpleMulticastDelegate OnUpdateSort;
	
	TArray<TWeakObjectPtr<USortBase>> DefaultSorts;
	TArray<TWeakObjectPtr<USortBase>> CurrentOptionSorts;

	TArray<USortBase*> Sorts;
	TArray<USortBase*> OptionSorts;
	bool bIsDescending = true;

private:
	TWeakObjectPtr<USortBase> PrioritySort = nullptr;
};
