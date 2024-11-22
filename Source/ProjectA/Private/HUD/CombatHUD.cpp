#include "HUD/CombatHUD.h"
#include "HUD/CharacterOverlay.h"
#include "HUD/PauseMenuWidget.h"
#include "HUD/ExitMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void ACombatHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CreateCharacterOverlay();
	ShowCharacterOverlay();
}

void ACombatHUD::ShowPauseMenu()
{
	if (PauseMenuWidgetClass)
	{
		PlayerController->bShowMouseCursor = true;
		PauseMenuWidget = CreateAndAddWidget<UPauseMenuWidget>(PauseMenuWidgetClass);
	}
}

void ACombatHUD::RemovePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;
	}
}

void ACombatHUD::ShowExitMenu()
{
	if (ExitMenuWidgetClass)
	{
		PlayerController->bShowMouseCursor = true;
		ExitMenuWidget = CreateAndAddWidget<UExitMenuWidget>(ExitMenuWidgetClass);
	}
}

void ACombatHUD::RemoveExitMenu()
{
	if (ExitMenuWidget)
	{
		ExitMenuWidget->RemoveFromParent();
		ExitMenuWidget = nullptr;
	}
}

void ACombatHUD::CreateCharacterOverlay()
{
	if (CharacterOverlayClass)
	{
		CharacterOverlay = CreateAndAddWidget<UCharacterOverlay>(CharacterOverlayClass);
	}
}

void ACombatHUD::RemoveCharacterOverlay()
{
	if (CharacterOverlay)
	{
		CharacterOverlay->RemoveFromParent();
		CharacterOverlay = nullptr;
	}
}

void ACombatHUD::ShowCharacterOverlay()
{
	if (CharacterOverlay)
	{
		PlayerController->bShowMouseCursor = false;
		CharacterOverlay->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACombatHUD::HideCharacterOverlay()
{
	if (CharacterOverlay)
	{
		CharacterOverlay->SetVisibility(ESlateVisibility::Hidden);
	}
}