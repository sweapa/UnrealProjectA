#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

UCLASS()
class PROJECTA_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnReturnBtnClicked();

	UFUNCTION()
	void OnRestartBtnClicked();

	UFUNCTION()
	void OnExitBtnClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitBtn;

private:
	class APlayerController* PlayerController;
	class ACombatHUD* CombatHUD;
};