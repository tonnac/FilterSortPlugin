// Fill out your copyright notice in the Description page of Project Settings.


#include "SortBase.h"

bool USortBase::IsActive() const
{
	return IsActiveEvent.Execute(this);
}

void USortBase::UpdateSort()
{
	OnUpdateSort.ExecuteIfBound(this);
}
