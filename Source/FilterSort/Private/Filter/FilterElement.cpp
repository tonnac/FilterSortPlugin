// Fill out your copyright notice in the Description page of Project Settings.


#include "FilterElement.h"

void UFilterElement::Initialize(int32 InIndex, void* Src)
{
	Index = InIndex;
}

int32 UFilterElement::GetIndex() const
{
	return Index;
}
