#include "Actors/ExitPoint.h"
#include "HUD/CombatHUD.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"

AExitPoint::AExitPoint()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	ExitEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	ExitEffect->SetupAttachment(GetRootComponent());
}

void AExitPoint::BeginPlay()
{
	Super::BeginPlay();

	ExitEffect->SetRelativeLocation(this->GetActorLocation());

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AExitPoint::OnSphereOverlap);

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CombatHUD = Cast<ACombatHUD>(PlayerController->GetHUD());
}

void AExitPoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CombatHUD && CombatHUD->GetExitMenuWidget()) return;

	if (CombatHUD)
	{
		CombatHUD->ShowExitMenu();
		CombatHUD->HideCharacterOverlay();
	}
}
