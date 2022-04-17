#pragma once
#include "FilterSortModule.h"
#include "SortBase.h"

template <typename TDataType>
class TSortContainer : public FGCObject
{
public:
	TSortContainer(UObject* Outer, TArray<UClass*> DefaultSortClasses = TArray<UClass*> {})
	{
		if (FFilterSortModule* FilterSortModule = FModuleManager::GetModulePtr<FFilterSortModule>("FilterSort"))
		{
			if (TArray<UClass*>* Classes = FilterSortModule->SortClasses.Find(TDataType::StaticClass()))
			{
				for (const UClass* SortClass : *Classes)
				{
					if (USortBase* NewSortBase = NewObject<USortBase>(Outer, SortClass))
					{
						NewSortBase->OnUpdateSort.BindRaw(this, &TSortContainer<TDataType>::UpdateSort);
						NewSortBase->IsDescending.BindRaw(this, &TSortContainer<TDataType>::IsDescending);
						NewSortBase->IsActiveEvent.BindRaw(this, &TSortContainer<TDataType>::IsActiveSort);
						Sorts.Emplace(NewSortBase);
					}
				}
			}
		}

		Sorts.Sort([](const USortBase& lhs, const USortBase& rhs)
		{
			return lhs.GetIndex() < rhs.GetIndex();
		});

		if (DefaultSortClasses.Num() == 0)
		{
			for (USortBase* Sort : Sorts)
			{
				DefaultSorts.Emplace(Sort);
			}
		}
		else
		{
			for (USortBase* Sort : Sorts)
			{
				UClass** FoundClass = DefaultSortClasses.FindByPredicate([Sort](const UClass* SortClass)
				{
					return Sort->GetClass() == SortClass;	
				});
				if (FoundClass)
				{
					DefaultSorts.Emplace(Sort);
				}
			}
		}

		if (PrioritySort.IsValid() == false)
		{
			UpdateSort(DefaultSorts[0].Get());
		}
	}

	void ApplySort(TArray<TDataType*>& Objects)
	{
		Objects.Sort(*this);
	}

	void ApplySort(TArray<const TDataType*>& Objects)
	{
		Objects.Sort(*this);
	}

	TOptional<bool> SortImplementation(const TArray<TWeakObjectPtr<USortBase>>& SortElements, const TDataType& lhs,
	                                   const TDataType& rhs) const
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

	bool operator()(const TDataType& lhs, const TDataType& rhs) const
	{
		if (TOptional<bool> bResult = SortImplementation({ PrioritySort }, lhs, rhs))
		{
			return bResult.GetValue();
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
