#include "Characters/ProjectACharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GroomComponent.h"
#include "Items/Item.h"
#include "Items/Soul.h"
#include "Items/Treasure.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "HUD/CombatHUD.h"
#include "HUD/CharacterOverlay.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProjectACharacter::AProjectACharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
}

void AProjectACharacter::Tick(float DeltaTime)
{
	if (Attributes && CharacterOverlay)
	{
		Attributes->RegenStamina(DeltaTime);
		CharacterOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void AProjectACharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);

	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::EAS_HitReaction;
	}
}

void AProjectACharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}

void AProjectACharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && CharacterOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		CharacterOverlay->SetSouls(Attributes->GetSouls());
	}
}

void AProjectACharacter::AddGold(ATreasure* Treasure)
{
	if (Attributes && CharacterOverlay)
	{
		Attributes->AddGold(Treasure->GetGold());
		CharacterOverlay->SetGold(Attributes->GetGold());
	}
}

void AProjectACharacter::UsePotion()
{
	if (Attributes && CharacterOverlay)
	{
		Attributes->UsePotion();
		SetHealthHUD();
		CharacterOverlay->SetPotions(Attributes->GetPotions());
	}

	if (HealEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HealEffect, GetActorLocation());
	}
}

void AProjectACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProjectACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectACharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectACharacter::Look);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &AProjectACharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Triggered, this, &AProjectACharacter::Interact);
		EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &AProjectACharacter::BasicAttack);
		EnhancedInputComponent->BindAction(StrongAttackAction, ETriggerEvent::Triggered, this, &AProjectACharacter::StrongAttack);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &AProjectACharacter::Dodge);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

float AProjectACharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHealthHUD();
	return DamageAmount;
}

void AProjectACharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CombatHUD = Cast<ACombatHUD>(PlayerController->GetHUD());
	InitializeCharacterOverlay();

	Tags.Add(FName("Player"));

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AProjectACharacter::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjectACharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectACharacter::EKeyPressed()
{
	if (Attributes->GetPotions() > 0)
	{
		UsePotion();
	}
}

void AProjectACharacter::Interact()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}

		EquipWeapon(OverlappingWeapon);
	}

	ASoul* OverlappingSoul = Cast<ASoul>(OverlappingItem);
	if (OverlappingSoul)
	{
		OverlappingSoul->AddSoul(this);
	}
}

void AProjectACharacter::BasicAttack()
{
	if (CanAttack())
	{
		EquippedWeapon->SetDamage(BasicAttackDamage);
		PlayBasicAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AProjectACharacter::StrongAttack()
{
	if (CanAttack())
	{
		EquippedWeapon->SetDamage(StrongAttackDamage);
		PlayStrongAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AProjectACharacter::Jump()
{
	if (IsUnoccupied())
	{
		Super::Jump();
	}
}

void AProjectACharacter::Dodge()
{
	if (IsOccupied() || !HasEnoughStamina()) return;
	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && CharacterOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		CharacterOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

void AProjectACharacter::Die()
{
	Super::Die();

	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();
}

bool AProjectACharacter::HasEnoughStamina()
{
	return Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}

bool AProjectACharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

void AProjectACharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedLongSword;
	OverlappingItem = nullptr;
	EquippedWeapon = Weapon;
}

void AProjectACharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AProjectACharacter::DodgeEnd()
{
	Super::DodgeEnd();

	ActionState = EActionState::EAS_Unoccupied;
}

bool AProjectACharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

void AProjectACharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool AProjectACharacter::IsUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

void AProjectACharacter::InitializeCharacterOverlay()
{
	if (!PlayerController || !CombatHUD) return;

	CharacterOverlay = Cast<UCharacterOverlay>(CombatHUD->GetCharacterOverlay());
	if (CharacterOverlay && Attributes)
	{
		SetHealthHUD();
		CharacterOverlay->SetStaminaBarPercent(1.f);
		CharacterOverlay->SetGold(0);
		CharacterOverlay->SetSouls(0);
		CharacterOverlay->SetPotions(5);
	}
}

void AProjectACharacter::SetHealthHUD()
{
	if (Attributes && CharacterOverlay)
	{
		CharacterOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}