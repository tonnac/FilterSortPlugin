#pragma once

template <typename T, typename = int32>
struct TFilterContainerFunctor
{
	template <typename U>
	bool operator()(T* _pFilterElementContainer, const U* _pData)
	{
		return true;
	}
};

template <typename T>
struct TFilterContainerFunctor <T, decltype((void)T::CurrentFilters, (int32)0)>
{
	template <typename U>
	bool operator()(T* _pFilterElementContainer, const U* _pData)
	{
		if (_pFilterElementContainer->IsEmpty())
		{
			return false;
		}

		for (const auto& Filter : _pFilterElementContainer->CurrentFilters)
		{
			if (Filter->Is_Satisfied(_pData))
			{
				return true;
			}
		}

		return false;
	}
};