#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverlay.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class PROJECTA_API UCharacterOverlay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetHealthBarPercent(float Percent);
	void SetStaminaBarPercent(float Percent);
	void SetResource(UTextBlock* TextBlock, int32 Resource);
	void SetGold(int32 Gold);
	void SetSouls(int32 Souls);
	void SetPotions(int32 Potions);

	UFUNCTION()
	void OnPauseBtnClicked();

private:
	class APlayerController* PlayerController;
	class ACombatHUD* CombatHUD;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SoulsCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionCount;

	UPROPERTY(meta = (BindWidget))
	class UButton* PauseBtn;
};