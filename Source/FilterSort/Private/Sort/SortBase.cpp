// Fill out your copyright notice in the Description page of Project Settings.


#include "SortBase.h"

void USortBase::UpdateSort()
{
	OnUpdateSort.ExecuteIfBound(this);
}
