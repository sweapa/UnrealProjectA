#include "Anim/ProjectAAnimInstance.h"
#include "Characters/ProjectACharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UProjectAAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ProjectACharacter = Cast<AProjectACharacter>(TryGetPawnOwner());

	if (ProjectACharacter)
	{
		ProjectACharacterMovement = ProjectACharacter->GetCharacterMovement();
	}
}

void UProjectAAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ProjectACharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(ProjectACharacterMovement->Velocity);
		IsFalling = ProjectACharacterMovement->IsFalling();
		CharacterState = ProjectACharacter->GetCharacterState();
		ActionState = ProjectACharacter->GetActionState();
	}
}