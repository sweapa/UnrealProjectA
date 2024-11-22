#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ProjectAGameMode.generated.h"

UCLASS(minimalapi)
class AProjectAGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProjectAGameMode();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OpenCombatLevel(FName LevelName);

private:
	TSubclassOf<class ADungeonGameMode> DungeonGameModeClass;
};