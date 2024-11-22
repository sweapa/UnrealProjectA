#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExitMenuWidget.generated.h"

UCLASS()
class PROJECTA_API UExitMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void BindWidgetEvents();

	UFUNCTION()
	void OnExitBtnClicked();

	UFUNCTION()
	void OnReturnBtnClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnBtn;

private:
	class APlayerController* PlayerController;
	class ACombatHUD* CombatHUD;
};
