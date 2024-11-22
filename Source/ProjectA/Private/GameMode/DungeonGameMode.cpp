#include "GameMode/DungeonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/CombatHUD.h"

ADungeonGameMode::ADungeonGameMode()
{
}

void ADungeonGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ADungeonGameMode::Restart(FName LevelName)
{
	this->ResetLevel();
	this->RestartPlayer(PlayerController);

	ACombatHUD* CombatHUD = Cast<ACombatHUD>(PlayerController->GetHUD());
	if (CombatHUD)
	{
		CombatHUD->RemovePauseMenu();
		CombatHUD->ShowCharacterOverlay();
	}
}