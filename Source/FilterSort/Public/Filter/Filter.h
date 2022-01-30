// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FilterInterface.h"
#include "FilterSortFunctor.h"
#include "Filter.generated.h"

#define IMPLEMENT_COMMON(TDataType, TClass)																			\
private:																											\
	virtual UClass* GetDataTypeClass() const override { return TDataType::StaticClass(); }							\
public:																												\
	virtual bool operator()(const TDataType* _pData) override { return TFilterFunctor<TClass>()(this, _pData); };	\
	virtual bool IsEmpty() override { return TFilterFunctor<TClass>::IsEmpty(this); };								\

#define IMPLEMENT_HASCONTAINER_FILTER(TDataType, TClass)	\
IMPLEMENT_COMMON(TDataType, TClass)							\
public:														\
	TSet<TFilterInterface<TDataType>*> CurrentFilters;

#define IMPLEMENT_HASNOTCONTAINER_FILTER(TDataType, TClass)	\
IMPLEMENT_COMMON(TDataType, TClass)							\
public:														\
	TFilterInterface<TDataType>* CurrentFilter;

class UAObject;
/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilter : public UObject
{
	GENERATED_BODY()

public:
	virtual bool operator()(const UAObject* _pData)	{ return false;	}
	
public:
	virtual void Initialize() PURE_VIRTUAL(UFilter::Initialize, );
	UFUNCTION()
	virtual UClass* GetDataTypeClass() const PURE_VIRTUAL(UFilter::GetDataTypeClass, return nullptr;);
	virtual bool IsEmpty() PURE_VIRTUAL(UFilter::IsEmpty, return false; );
};