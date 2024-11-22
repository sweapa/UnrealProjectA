#include "GameMode/ProjectAGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameMode/DungeonGameMode.h"

AProjectAGameMode::AProjectAGameMode()
{
	static ConstructorHelpers::FClassFinder<ADungeonGameMode> DungeonGameModeBPClass(TEXT("/Game/Blueprints/GameMode/BP_DungeonGameMode"));
	if (DungeonGameModeBPClass.Succeeded())
	{
		DungeonGameModeClass = DungeonGameModeBPClass.Class;
	}
}

void AProjectAGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectAGameMode::OpenCombatLevel(FName LevelName)
{
	if (LevelName.IsNone() || !DungeonGameModeClass) return;

	FString Options = FString::Printf(TEXT("?game=%s"), *DungeonGameModeClass->GetPathName());
	FString URL = LevelName.ToString() + Options;

	UGameplayStatics::OpenLevel(this, FName(*URL));
}