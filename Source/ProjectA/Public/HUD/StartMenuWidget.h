#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

UCLASS()
class PROJECTA_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartBtnClicked();

	UFUNCTION()
	void OnExitBtnClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* StartBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitBtn;

private:
	class APlayerController* PlayerController;
	class AProjectHUD* ProjectHUD;
};
