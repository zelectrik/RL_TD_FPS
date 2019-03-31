// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPlayerController.h"

ABasicPlayerController::ABasicPlayerController()
{
	SetActorTickEnabled(true);
	m_MovementController = CreateDefaultSubobject<UMovementController>(TEXT("Movement controller"));
	m_MovementController->RegisterComponent();

	
	
}

void ABasicPlayerController::BeginPlay()
{
	m_CharacterOwner = Cast<ABasicCharacter>(GetPawn());
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	m_RightWeapon = GetWorld()->SpawnActor<ABaseWeapon>(Location, Rotation, SpawnInfo);
	m_RightWeapon->AttachToComponent((USceneComponent*)m_CharacterOwner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), "HandRSocket");

	m_LeftWeapon = GetWorld()->SpawnActor<ABaseWeapon>(Location, Rotation, SpawnInfo);
	m_LeftWeapon->AttachToComponent((USceneComponent*)m_CharacterOwner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), "HandLSocket");

}

void ABasicPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Controller tick"));
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
