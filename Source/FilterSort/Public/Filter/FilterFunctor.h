#pragma once
#include "FilterInterface.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/TileView.h"
#include "Widget/FilterElementList.h"
#include "Widget/FilterWidget.h"

template <typename T, typename = int32>
struct TFilterFunctor
{
	template <typename U>
	bool operator()(T* _pFilter, const U* _pData)
	{
		if (_pFilter->IsEmpty())
		{
			return false;
		}
		return _pFilter->CurrentFilter->operator()(_pData);
	}
	
	static void UpdateFilter(T* _pFilter, UFilterElement* _pFilterElement)
	{
		_pFilter->CurrentFilter = _pFilter->CurrentFilter != nullptr ? nullptr : _pFilterElement;
	}

	static bool IsEmpty(T* _pFilter)
	{
		return _pFilter->CurrentFilter == nullptr;
	}

	static void BuildWidget(T* _pFilter, UFilterWidget* _pFilterWidget)
	{
		
	}
};

template <typename T>
struct TFilterFunctor <T, decltype((void)T::CurrentFilters, (int32)0)>
{
	template <typename U>
	bool operator()(T* _pFilter, const U* _pData)
	{
		if (_pFilter->IsEmpty())
		{
			return false;
		}

		for (const auto& Filter : _pFilter->CurrentFilters)
		{
			if (Filter->operator()(_pData))
			{
				return true;
			}
		}

		return false;
	}
	
	static void UpdateFilter(T* _pFilter, UFilterElement* _pFilterElement)
	{
		if (_pFilter->CurrentFilters.Contains(_pFilterElement))
		{
			_pFilter->CurrentFilters.Remove(_pFilterElement);
		}
		else
		{
			_pFilter->CurrentFilters.Emplace(_pFilterElement);
		}
	}

	static bool IsEmpty(T* _pFilter)
	{
		return _pFilter->CurrentFilters.Num() == 0;
	}

	static void BuildWidget(T* _pFilter, UFilterWidget* _pFilterWidget)
	{
		_pFilterWidget->CheckBox->SetCheckedState(_pFilter->IsEmpty() ? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
		_pFilterWidget->TextBlock->SetText(_pFilter->GetFilterName());
		_pFilterWidget->FilterElementList->TileView->SetListItems(_pFilter->Filters);
	}
};