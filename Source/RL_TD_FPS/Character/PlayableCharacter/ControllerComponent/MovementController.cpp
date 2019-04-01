// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementController.h"
#include "Character/PlayableCharacter/BasicPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UMovementController::UMovementController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	/*PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;*/
	m_MovementSettings = F_MovementSettings();
	m_MovementSettings.b_EnableCameraFollowRotation = false;
	m_MovementSettings.m_NumberJumpCanBeDone = 2;
	b_DisableMovement = false;
	b_DisableRotation = false;
	m_RightRotationValue = 0;
	m_ForwardSpeedInput = 0;
	m_RightSpeedInput = 0;
	m_CurrentJumpDone = 0;
	b_JumpStart = false;
	// ...
}


// Called when the game starts
void UMovementController::BeginPlay()
{
	Super::BeginPlay();
}

void UMovementController::PostInitProperties()
{
	Super::PostInitProperties();
}

void UMovementController::UpdateMovementController(float DeltaTime)
{
	if (b_JumpStart)
	{
		b_JumpStart = false;
	}
	else if (m_CurrentJumpDone > 0)
	{
		if (ABasicCharacter * l_CharacterPlayer = GetCharacterPawn())
		{
			if (!l_CharacterPlayer->GetCharacterMovement()->IsFalling())
			{
				m_CurrentJumpDone = 0;
			}
		}
	}
}

void UMovementController::MoveForward(float p_Value)
{
	if (!b_DisableMovement)
	{
		if (ABasicCharacter * l_Pawn = GetCharacterPawn())
		{
			m_ForwardSpeedInput = p_Value;
			FVector l_ForwardVector = l_Pawn->GetActorForwardVector();
			l_ForwardVector.Z = 0;
			l_ForwardVector.Normalize();
			l_Pawn->AddMovementInput(l_ForwardVector, p_Value);
		}
	}
	else
	{
		m_ForwardSpeedInput = 0;
	}
}

void UMovementController::MoveRight(float p_Value)
{
	if (!b_DisableMovement)
	{
		if (ABasicCharacter * l_Pawn = GetCharacterPawn())
		{
			m_RightSpeedInput = p_Value;
			FVector l_RightVector = l_Pawn->GetActorRightVector();
			l_RightVector.Z = 0;
			l_RightVector.Normalize();
			l_Pawn->AddMovementInput(l_RightVector, p_Value);
		}
	}
	else
	{
		m_RightSpeedInput = 0;
	}
}

void UMovementController::LookUp(float p_Value)
{
	if (!b_DisableRotation)
	{
		if (ABasicCharacter * l_Pawn = GetCharacterPawn())
		{
			float l_GlobalTimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
			float l_RotateValue = p_Value * m_MovementSettings.m_Sensitivity * m_MovementSettings.m_InverseUpRotation;
			if (l_GlobalTimeDilation != 1)
			{
				l_RotateValue *= l_GlobalTimeDilation;
			}
			l_Pawn->AddControllerPitchInput(l_RotateValue);
		}
	}
}

void UMovementController::LookRight(float p_Value)
{
	if (!b_DisableRotation)
	{
		if (ABasicCharacter * l_Pawn = GetCharacterPawn())
		{
			float l_GlobalTimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
			float l_RotateValue = p_Value * m_MovementSettings.m_Sensitivity;
			
			m_RightRotationValue += (l_RotateValue - m_RightRotationValue) * 0.2;

			if (l_GlobalTimeDilation != 1)
			{
				l_RotateValue *= l_GlobalTimeDilation;
			}
			l_Pawn->AddControllerYawInput(l_RotateValue);
			if (m_MovementSettings.b_EnableCameraFollowRotation)
			{
				FRotator l_CameraRotation = GetOwnerController()->GetControlRotation();
				l_CameraRotation.Roll = m_RightRotationValue * .5;
				GetOwnerController()->SetControlRotation(l_CameraRotation);
			}
		}
	}
}

void UMovementController::OnJumpInputPressed()
{
	
	ABasicCharacter* l_CharacterPlayer = GetCharacterPawn();
	if (!l_CharacterPlayer->GetCharacterMovement()->IsFalling())
	{
		if (m_MovementSettings.m_NumberJumpCanBeDone >= 1)
		{
			l_CharacterPlayer->bPressedJump = true;
			m_CurrentJumpDone = 1;
			b_JumpStart = true;
		}

	}
	else
	{
		if (m_CurrentJumpDone < m_MovementSettings.m_NumberJumpCanBeDone)
		{
			m_CurrentJumpDone++;
			FVector l_LaunchVector;
			l_LaunchVector.X = m_ForwardSpeedInput;
			l_LaunchVector.Y = m_RightSpeedInput;
			l_LaunchVector.Z = 1;
			FRotator l_CharacterRotation = FRotator(0, l_CharacterPlayer->GetControlRotation().Yaw, 0);
			l_LaunchVector = l_CharacterRotation.RotateVector(l_LaunchVector);
			l_LaunchVector.Normalize();
			l_LaunchVector *= m_MovementSettings.m_DoubleJumpVelocity;
			l_CharacterPlayer->LaunchCharacter(l_LaunchVector, true, true);
		}
	}
	/*
	if (!l_CharacterPlayer->GetCharacterMovement()->IsFalling())
	{
		if (m_MovementSettings.m_JumpAbilities.Contains(E_JumpABilities::VE_BasicJump))
		{
			l_CharacterPlayer->bPressedJump = true;
		}
	}
	else
	{
		if (b_CanDoubleJump)
		{
			if (m_MovementSettings.m_JumpAbilities.Contains(E_JumpABilities::VE_DoubleJump))
			{
				FVector l_LaunchVector;
				l_LaunchVector.X = m_ForwardSpeedInput;
				l_LaunchVector.Y = m_RightSpeedInput;
				l_LaunchVector.Z = 1;
				FRotator l_CharacterRotation = FRotator(0, l_CharacterPlayer->GetControlRotation().Yaw, 0);
				l_LaunchVector = l_CharacterRotation.RotateVector(l_LaunchVector);
				l_LaunchVector.Normalize();
				l_LaunchVector *= m_MovementSettings.m_DoubleJumpVelocity;
				l_CharacterPlayer->LaunchCharacter(l_LaunchVector, true, true);
				b_CanDoubleJump = false;
			}
		}
	}*/
}

void UMovementController::OnJumpInputReleased()
{
	ABasicCharacter* l_CharacterPlayer = GetCharacterPawn();
	l_CharacterPlayer->bPressedJump = false;
}

void UMovementController::UpdateDisabledElement(bool p_DisableMovement, bool p_DisableRotation)
{
	b_DisableMovement = p_DisableMovement;
	b_DisableRotation = p_DisableRotation;
}


ABasicPlayerController * UMovementController::GetOwnerController()
{
	return Cast<ABasicPlayerController>(GetOwner());
}

ABasicCharacter * UMovementController::GetCharacterPawn()
{
	if(ABasicPlayerController * l_ownerController = GetOwnerController())
		return l_ownerController->GetCharacterPawn();
	return nullptr;
}


void UMovementController::SetupCharacterMovement()
{
	if (ABasicCharacter* l_CharacterPawn = GetCharacterPawn())
	{
		l_CharacterPawn->GetCharacterMovement()->AirControl = m_MovementSettings.m_AirControl;
		l_CharacterPawn->GetCharacterMovement()->JumpZVelocity = m_MovementSettings.m_FirstJumpZVelocity;
	}
}

float UMovementController::GetRightRotationValue()
{
	return m_RightRotationValue;
}

float UMovementController::GetForwardSpeedInput()
{
	return m_ForwardSpeedInput;
}

float UMovementController::GetRightSpeedInput()
{
	return m_RightSpeedInput;
}
