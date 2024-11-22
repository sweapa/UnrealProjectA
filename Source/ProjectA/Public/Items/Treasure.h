#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Treasure.generated.h"

UCLASS()
class PROJECTA_API ATreasure : public AItem
{
	GENERATED_BODY()
	
public:
	FORCEINLINE int32 GetGold() const { return Gold; }

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;
};
