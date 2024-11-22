#include "Items/Soul.h"
#include "Interfaces/PickupInterface.h"

void ASoul::AddSoul(AActor* OverlappingActor)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OverlappingActor);
	if (PickupInterface)
	{
		PickupInterface->AddSouls(this);
		SpawnPickupSystem();
		SpawnPickupSound();

		Destroy();
	}
}