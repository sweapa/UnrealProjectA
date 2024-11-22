#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatHUD.generated.h"

class UCharacterOverlay;
class UPauseMenuWidget;
class UExitMenuWidget;
class UUserWidget;

UCLASS()
class PROJECTA_API ACombatHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void ShowPauseMenu();
	void RemovePauseMenu();
	void ShowExitMenu();
	void RemoveExitMenu();
	void CreateCharacterOverlay();
	void RemoveCharacterOverlay();
	void ShowCharacterOverlay();
	void HideCharacterOverlay();

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UCharacterOverlay> CharacterOverlayClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UExitMenuWidget> ExitMenuWidgetClass;

	FORCEINLINE UCharacterOverlay* GetCharacterOverlay() const { return CharacterOverlay; }
	FORCEINLINE UExitMenuWidget* GetExitMenuWidget() const { return ExitMenuWidget; }

protected:
	template<typename T>
	T* CreateAndAddWidget(TSubclassOf<UUserWidget> WidgetClass);

	UPROPERTY()
	UCharacterOverlay* CharacterOverlay;

	UPROPERTY()
	UPauseMenuWidget* PauseMenuWidget;

	UPROPERTY()
	UExitMenuWidget* ExitMenuWidget;

	class APlayerController* PlayerController;
};

template<typename T>
inline T* ACombatHUD::CreateAndAddWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	if (WidgetClass)
	{
		T* Widget = CreateWidget<T>(GetWorld(), WidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
		return Widget;
	}
	return nullptr;
}