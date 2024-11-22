#include "HUD/ProjectHUD.h"
#include "HUD/StartMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void AProjectHUD::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;
	ShowStartMenu();
}

void AProjectHUD::ShowStartMenu()
{
	if (StartMenuWidgetClass)
	{
		StartMenuWidget = CreateWidget<UStartMenuWidget>(GetWorld(), StartMenuWidgetClass);
		StartMenuWidget->AddToViewport();
	}
}

void AProjectHUD::RemoveStartMenu()
{
	if (StartMenuWidget)
	{
		StartMenuWidget->RemoveFromParent();
		StartMenuWidget = nullptr;
	}
}