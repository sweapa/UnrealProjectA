#include "HUD/StartMenuWidget.h"
#include "HUD/ProjectHUD.h"
#include "Components/Button.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameMode/ProjectAGameMode.h"

void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	ProjectHUD = Cast<AProjectHUD>(PlayerController->GetHUD());

	if (StartBtn)
	{
		StartBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnStartBtnClicked);
	}

	if (ExitBtn)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnExitBtnClicked);
	}
}

void UStartMenuWidget::OnStartBtnClicked()
{
	AProjectAGameMode* GameMode = Cast<AProjectAGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->OpenCombatLevel("Cave_Ruins_Demo");
		ProjectHUD->RemoveStartMenu();
	}
}

void UStartMenuWidget::OnExitBtnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}