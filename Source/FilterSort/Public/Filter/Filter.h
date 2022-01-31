// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FilterInterface.h"
#include "FilterSortFunctor.h"
#include "Filter.generated.h"

#define DECLARE_DATATYPE(TDataType)													\
	public:																			\
		virtual bool operator()(const TDataType* _pData)	{ return false;	}		\
		virtual void UpdateFilter(TFilterInterface<TDataType>* _pFilterInterface) {}


#define IMPLEMENT_COMMON_FILTER(TDataType, TClass, Index)																							\
private:																																			\
	virtual UClass* GetDataTypeClass() const override { return TDataType::StaticClass(); }															\
public:																																				\
	virtual bool operator()(const TDataType* _pData) override { return TFilterFunctor<TClass>()(this, _pData); }						\
	virtual void UpdateFilter(TFilterInterface<TDataType>* _pFilterInterface) { TFilterFunctor<TClass>::UpdateFilter(this, _pFilterInterface); }		\
	bool IsEmpty() { return TFilterFunctor<TClass>::IsEmpty(this); };																			\
	virtual int32 GetIndex() const override { return Index; }

#define IMPLEMENT_HASCONTAINER_FILTER(TDataType, TClass, Index) \
IMPLEMENT_COMMON_FILTER(TDataType, TClass, Index)				 \
public:													 \
	TSet<TFilterInterface<TDataType>*> CurrentFilters;

#define IMPLEMENT_FILTER(TDataType, TClass, Index)	\
IMPLEMENT_COMMON_FILTER(TDataType, TClass, Index)	\
public:										\
	TFilterInterface<TDataType>* CurrentFilter;

class UAObject;
/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UFilter : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_DATATYPE(UAObject)
	
public:
	virtual void Initialize() PURE_VIRTUAL(UFilter::Initialize, );
	UFUNCTION()
	virtual UClass* GetDataTypeClass() const PURE_VIRTUAL(UFilter::GetDataTypeClass, return nullptr;);
	virtual int32 GetIndex() const PURE_VIRTUAL(UFilter::GetIndex, return -1;);
};