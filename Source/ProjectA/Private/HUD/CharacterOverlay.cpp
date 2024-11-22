#include "HUD/CharacterOverlay.h"
#include "HUD/CombatHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UCharacterOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CombatHUD = Cast<ACombatHUD>(PlayerController->GetHUD());

	if (PauseBtn)
	{
		PauseBtn->OnClicked.AddDynamic(this, &UCharacterOverlay::OnPauseBtnClicked);
	}
}

void UCharacterOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UCharacterOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void UCharacterOverlay::SetResource(UTextBlock* TextBlock, int32 Resource)
{
	if (TextBlock)
	{
		const FString String = FString::Printf(TEXT("%d"), Resource);
		const FText Text = FText::FromString(String);
		TextBlock->SetText(Text);
	}
}

void UCharacterOverlay::SetGold(int32 Gold)
{
	SetResource(GoldCount, Gold);
}

void UCharacterOverlay::SetSouls(int32 Souls)
{
	SetResource(SoulsCount, Souls);
}

void UCharacterOverlay::SetPotions(int32 Potions)
{
	SetResource(PotionCount, Potions);
}

void UCharacterOverlay::OnPauseBtnClicked()
{
	if (CombatHUD)
	{
		CombatHUD->HideCharacterOverlay();
		CombatHUD->ShowPauseMenu();
	}
}