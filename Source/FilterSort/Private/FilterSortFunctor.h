#pragma once

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
		return _pFilter->CurrentFilter->Is_Satisfied(_pData);
	}

	template <typename U>
	static void UpdateFilter(T* _pFilter, TFilterInterface<U>* _pFilterInterface)
	{
		_pFilter->CurrentFilter = _pFilter->CurrentFilter != nullptr ? nullptr : _pFilterInterface;
	}

	static bool IsEmpty(T* _pFilter)
	{
		return _pFilter->CurrentFilter == nullptr;
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
			if (Filter->Is_Satisfied(_pData))
			{
				return true;
			}
		}

		return false;
	}

	template <typename U>
	static void UpdateFilter(T* _pFilter, TFilterInterface<U>* _pFilterInterface)
	{
		if (_pFilter->CurrentFilters.Contains(_pFilterInterface))
		{
			_pFilter->CurrentFilters.Remove(_pFilterInterface);
		}
		else
		{
			_pFilter->CurrentFilters.Emplace(_pFilterInterface);
		}
	}

	static bool IsEmpty(T* _pFilter)
	{
		return _pFilter->CurrentFilters.Num() == 0;
	}
};