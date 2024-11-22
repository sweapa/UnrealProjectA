#include "HUD/PauseMenuWidget.h"
#include "HUD/CombatHUD.h"
#include "GameMode/DungeonGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CombatHUD = Cast<ACombatHUD>(PlayerController->GetHUD());

	if (ReturnBtn)
	{
		ReturnBtn->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnReturnBtnClicked);
	}

	if (RestartBtn)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnRestartBtnClicked);
	}

	if (ExitBtn)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnExitBtnClicked);
	}
}

void UPauseMenuWidget::OnReturnBtnClicked()
{
	if (CombatHUD)
	{
		CombatHUD->RemovePauseMenu();
		CombatHUD->ShowCharacterOverlay();
	}
}

void UPauseMenuWidget::OnRestartBtnClicked()
{
	ADungeonGameMode* GameMode = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->Restart("Cave_Ruins_Demo");
	}
}

void UPauseMenuWidget::OnExitBtnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}