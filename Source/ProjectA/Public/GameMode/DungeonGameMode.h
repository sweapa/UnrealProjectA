#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonGameMode.generated.h"

UCLASS()
class PROJECTA_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADungeonGameMode();
	virtual void BeginPlay() override;

	UFUNCTION()
	void Restart(FName LevelName);

private:
	class APlayerController* PlayerController;
};