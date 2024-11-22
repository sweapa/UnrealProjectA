#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExitPoint.generated.h"

UCLASS()
class PROJECTA_API AExitPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AExitPoint();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ExitEffect;

private:
	class APlayerController* PlayerController;
	class ACombatHUD* CombatHUD;
};