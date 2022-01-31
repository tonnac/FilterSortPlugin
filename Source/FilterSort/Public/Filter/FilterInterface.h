#pragma once


template <typename T>
class TFilterInterface
{
public:
	explicit TFilterInterface(int32 Index)
		: Index(Index)
	{}
	
	virtual ~TFilterInterface() = default;
	int32 GetIndex() const { return Index; }
	virtual bool Is_Satisfied(const T* Data) = 0;

private:
	int32 Index = 0;
};
