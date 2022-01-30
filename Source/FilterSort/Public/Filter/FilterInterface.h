#pragma once


template <typename T>
class TFilterInterface
{
public:
	virtual ~TFilterInterface() = default;
	static UClass* GetDataClass() { return T::StaticClass(); }
	virtual bool Is_Satisfied(const T* Data) = 0;
};
