// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FilterSortHUD.generated.h"

class UFilterListWidget;

/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterSortHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFilterListWidget* GetFilterList() const { return FilterList; }
	
private:
	UPROPERTY(meta=(BindWidget))
	UFilterListWidget* FilterList = nullptr;
};
