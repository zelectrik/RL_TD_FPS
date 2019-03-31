// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/PlayableCharacter/BasicCharacter.h"
#include "MovementController.generated.h"

class ABasicPlayerController;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class E_JumpABilities : uint8
{
	VE_BasicJump 	UMETA(DisplayName = "BasicJump"),
	VE_DoubleJump 	UMETA(DisplayName = "DoubleJump"),
	VE_Climb		UMETA(DisplayName = "Climb"),
	VE_Plane		UMETA(DisplayName = "Plane")
};

//If you want this to appear in BP, make sure to use this instead
//USTRUCT(BlueprintType)
USTRUCT()
struct F_MovementSettings
{
	GENERATED_BODY()

	UPROPERTY()
		bool b_EnableCameraFollowRotation;

	UPROPERTY(meta = (ClampMin = "-1", ClampMax = "1"))
		int8 m_InverseUpRotation;

	UPROPERTY(meta = (ClampMin = "0", ClampMax = "5"))
		float m_Sensitivity;

	UPROPERTY()
		int m_DoubleJumpVelocity;

	UPROPERTY()
		float m_FirstJumpZVelocity;

	UPROPERTY()
		float m_AirControl;

	UPROPERTY()
		TArray<E_JumpABilities> m_JumpAbilities;
	//Constructor
	F_MovementSettings()
	{
		b_EnableCameraFollowRotation = true;
		m_InverseUpRotation = -1;
		m_Sensitivity = 1.5f;
		m_FirstJumpZVelocity = 500;
		m_DoubleJumpVelocity = 500;
		m_AirControl = 0.5;
		m_JumpAbilities = TArray<E_JumpABilities>();
		m_JumpAbilities.Add(E_JumpABilities::VE_BasicJump);
		
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RL_TD_FPS_API UMovementController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UFUNCTION()
		void UpdateMovementController(float DeltaTime);

	UFUNCTION()
		void MoveForward(float p_Value);
	
	UFUNCTION()
		void MoveRight(float p_Value);

	UFUNCTION()
		void LookUp(float p_Value);

	UFUNCTION()
		void LookRight(float p_Value);

	UFUNCTION()
		void OnJumpInputPressed();

	UFUNCTION()
		void OnJumpInputReleased();

	UFUNCTION()
		void UpdateDisabledElement(bool p_DisableMovement = false, bool p_DisableRotation = false);

	UFUNCTION()
		void SetupCharacterMovement();

	UFUNCTION(BlueprintCallable)
		float GetRightRotationValue();

	UFUNCTION(BlueprintCallable)
		float GetForwardSpeedInput();

	UFUNCTION(BlueprintCallable)
		float GetRightSpeedInput();
	
	UPROPERTY()
		float m_RightRotationValue;

	UPROPERTY()
		float m_ForwardSpeedInput;

	UPROPERTY()
		float m_RightSpeedInput;


private:
	UFUNCTION()
		ABasicPlayerController* GetOwnerController();

	UFUNCTION()
		ABasicCharacter* GetCharacterPawn();

	UPROPERTY()
		F_MovementSettings m_MovementSettings;

	UPROPERTY()
		bool b_DisableMovement;

	UPROPERTY()
		bool b_DisableRotation;

	UPROPERTY()
		bool b_CanDoubleJump;



};
