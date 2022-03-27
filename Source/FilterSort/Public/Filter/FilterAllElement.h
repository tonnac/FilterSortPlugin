#pragma once

#include "CoreMinimal.h"
#include "FilterElement.h"
#include "FilterAllElement.generated.h"

/**
 * 
 */
UCLASS()
class FILTERSORT_API UFilterAllElement : public UFilterElement
{
	GENERATED_BODY()

public:
	virtual void Initialize(void* Src) override {}
};
