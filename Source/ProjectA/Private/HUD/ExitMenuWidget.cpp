#include "HUD/ExitMenuWidget.h"
#include "HUD/CombatHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UExitMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CombatHUD = Cast<ACombatHUD>(PlayerController->GetHUD());

	BindWidgetEvents();
}

void UExitMenuWidget::BindWidgetEvents()
{
	if (ExitBtn)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UExitMenuWidget::OnExitBtnClicked);
	}

	if (ReturnBtn)
	{
		ReturnBtn->OnClicked.AddDynamic(this, &UExitMenuWidget::OnReturnBtnClicked);
	}
}

void UExitMenuWidget::OnExitBtnClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
}

void UExitMenuWidget::OnReturnBtnClicked()
{
	if (CombatHUD)
	{
		CombatHUD->RemoveExitMenu();
		CombatHUD->ShowCharacterOverlay();
	}
}
