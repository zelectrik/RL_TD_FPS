// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPlayerController.h"
#include "Weapon/MechanicWeapon.h"

ABasicPlayerController::ABasicPlayerController()
{
	SetActorTickEnabled(true);
	m_MovementController = CreateDefaultSubobject<UMovementController>(TEXT("Movement controller"));

	
	
}

void ABasicPlayerController::BeginPlay()
{
	m_CharacterOwner = Cast<ABasicCharacter>(GetPawn());
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	m_RightWeapon = GetWorld()->SpawnActor<AMechanicWeapon>(Location, Rotation, SpawnInfo);
	m_RightWeapon->AttachToComponent((USceneComponent*)m_CharacterOwner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), "HandRSocket");
	m_RightWeapon->SetCharacterController(this);

	m_LeftWeapon = GetWorld()->SpawnActor<AMechanicWeapon>(Location, Rotation, SpawnInfo);
	m_LeftWeapon->AttachToComponent((USceneComponent*)m_CharacterOwner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), "HandLSocket");
	m_LeftWeapon->SetCharacterController(this);
}

void ABasicPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_MovementController->UpdateMovementController(DeltaTime);
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Example : InputComponent->BindAxis("MoveForward", this->m_MovementController, &UMovementController::MoveForward);

	InputComponent->BindAxis("MoveForward", this->m_MovementController, &UMovementController::MoveForward);
	InputComponent->BindAxis("MoveRight", this->m_MovementController, &UMovementController::MoveRight);

	InputComponent->BindAxis("LookUp", this->m_MovementController, &UMovementController::LookUp);
	InputComponent->BindAxis("LookRight", this->m_MovementController, &UMovementController::LookRight);

	InputComponent->BindAction("Jump", IE_Pressed, this->m_MovementController, &UMovementController::OnJumpInputPressed);
	InputComponent->BindAction("Jump", IE_Released, this->m_MovementController, &UMovementController::OnJumpInputReleased);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ABasicPlayerController::OnFirePressed);
	InputComponent->BindAction("Fire", IE_Released, this, &ABasicPlayerController::OnFireReleased);
}

void ABasicPlayerController::PostInitProperties()
{
	Super::PostInitProperties();
}

ABasicCharacter * ABasicPlayerController::GetCharacterPawn()
{
	return m_CharacterOwner;
}

UMovementController * ABasicPlayerController::GetMovementController()
{
	return m_MovementController;
}

void ABasicPlayerController::InitializeController()
{
	m_MovementController->SetupCharacterMovement();
}

void ABasicPlayerController::ApplyRecoil(float _strength, TSubclassOf<UCameraShake> _cameraShake)
{
	float PitchInput = -_strength / 100.f;
	PitchInput = FMath::RandRange(PitchInput * 0.5f, PitchInput * 1.5f);
	GetCharacterPawn()->AddControllerPitchInput(PitchInput);
	PlayerCameraManager->PlayCameraShake(_cameraShake, .5f);
	//GetCharacterPawn()->AddControllerYawInput(_strength/200.f);
}

void ABasicPlayerController::OnFirePressed()
{
	UE_LOG(LogTemp, Warning, TEXT("OnFirePressed"));
	if (m_LeftWeapon)
	{
		m_LeftWeapon->Fire();
	}
	if (m_RightWeapon)
	{
		m_RightWeapon->Fire();
	}
}

void ABasicPlayerController::OnFireReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("OnFireReleased"));
	if (m_LeftWeapon)
	{
		m_LeftWeapon->StopFire();
	}
	if (m_RightWeapon)
	{
		m_RightWeapon->StopFire();
	}
}

