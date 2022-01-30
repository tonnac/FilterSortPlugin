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

	static bool IsEmpty(T* _pFilter)
	{
		return _pFilter->CurrentFilters.Num() == 0;
	}
};