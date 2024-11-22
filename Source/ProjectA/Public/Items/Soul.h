#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Soul.generated.h"

UCLASS()
class PROJECTA_API ASoul : public AItem
{
	GENERATED_BODY()

public:
	void AddSoul(AActor* OverlappingActor);

	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }

protected:
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 Souls;
};