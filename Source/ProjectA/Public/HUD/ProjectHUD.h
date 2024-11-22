#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectHUD.generated.h"

class UStartMenuWidget;

UCLASS()
class PROJECTA_API AProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void ShowStartMenu();
	void RemoveStartMenu();

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UStartMenuWidget> StartMenuWidgetClass;

protected:
	UPROPERTY()
	UStartMenuWidget* StartMenuWidget;
};