﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FilterSortModule.h"
#include "UObject/Object.h"
#include "FilterElement.h"
#include "Filter/FilterFunctor.h"
#include "Filter.generated.h"


#define IMPLEMENT_COMMON_FILTER(TDataType, TClass, Index)																	\
private:																													\
	virtual UClass* GetDataTypeClass() const override { return TDataType::StaticClass(); }									\
public:																														\
	virtual bool operator()(const TDataType* _pData) override { return TFilterFunctor<TClass>()(this, _pData); }			\
	virtual void UpdateFilter(UFilterElement* _pFilterElement)																\
	{																														\
		TFilterFunctor<TClass>::UpdateFilter(this, _pFilterElement);														\
		OnUpdateFilter.ExecuteIfBound(this, _pFilterElement);																\
	}																														\
	virtual void BuildWidget(UFilterWidget* _pFilterWidget) { TFilterFunctor<TClass>::BuildWidget(this, _pFilterWidget); }	\
	bool IsEmpty() { return TFilterFunctor<TClass>::IsEmpty(this); };														\
	virtual int32 GetIndex() const override { return Index; }

#define IMPLEMENT_HASCONTAINER_FILTER(TDataType, TClass, Index) \
IMPLEMENT_COMMON_FILTER(TDataType, TClass, Index)				\
public:															\
	UPROPERTY()													\
	TArray<UFilterElement*> Filters;							\
	TSet<TWeakObjectPtr<UFilterElement>> CurrentFilters;

#define IMPLEMENT_FILTER(TDataType, TClass, Index)				\
IMPLEMENT_COMMON_FILTER(TDataType, TClass, Index)				\
public:															\
	UPROPERTY()													\
	UFilterElement* Filter = nullptr;							\
	TWeakObjectPtr<UFilterElement> CurrentFilter = nullptr;

class UAObject;
/**
 * 
 */
UCLASS(Abstract)
class FILTERSORT_API UFilter : public UObject
{
	GENERATED_BODY()
	

public:
	ADD_DATATYPE(UAObject)
	
public:
	virtual void UpdateFilter(UFilterElement* _pFilterElement) PURE_VIRTUAL(UFilter::UpdateFilter, );
	virtual FText GetFilterName() PURE_VIRTUAL(UFilter::GetFilterName, return FText::GetEmpty(););
	
	virtual void Initialize() PURE_VIRTUAL(UFilter::Initialize, )
	UFUNCTION()
	virtual UClass* GetDataTypeClass() const PURE_VIRTUAL(UFilter::GetDataTypeClass, return nullptr;);
	virtual int32 GetIndex() const PURE_VIRTUAL(UFilter::GetIndex, return -1;);
	virtual void BuildWidget(UFilterWidget* _pFilterWidget) PURE_VIRTUAL(UFilter::BuildWidget, );

public:
	DECLARE_DELEGATE_TwoParams(FOnUpdateFilter, UFilter*, UFilterElement*)
	FOnUpdateFilter OnUpdateFilter;
};