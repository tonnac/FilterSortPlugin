// Fill out your copyright notice in the Description page of Project Settings.


#include "AllFilter.h"


FText UAllFilter::GetFilterName()
{
	return FText::FromString(TEXT("All"));
}

bool UAllFilter::IsActive() const
{
	if (GetIsActive.IsBound())
	{
		return GetIsActive.Execute();
	}
	return false;
}
