// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterBase.h"

void UFilterBase::UpdateFilter(UFilterElement* FilterElement)
{
	OnUpdateFilter.ExecuteIfBound(this, FilterElement);
}
