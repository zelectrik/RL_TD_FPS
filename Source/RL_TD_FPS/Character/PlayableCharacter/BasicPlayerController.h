// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/PlayableCharacter/BasicCharacter.h"
#include "ControllerComponent/MovementController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Weapon/BaseWeapon.h"
#include "BasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RL_TD_FPS_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

	ABasicPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	/** PostInitProperties override. */
	virtual void PostInitProperties() override;

	UFUNCTION()
		ABasicCharacter* GetCharacterPawn();

	UFUNCTION(BlueprintCallable)
		UMovementController* GetMovementController();

	UFUNCTION()
		void InitializeController();

	UFUNCTION()
		void ApplyRecoil(float _strength);

	UPROPERTY()
		ABaseWeapon* m_RightWeapon;

	UPROPERTY()
		ABaseWeapon* m_LeftWeapon;
	
private:
	UFUNCTION()
		void OnFirePressed();

	UFUNCTION()
		void OnFireReleased();

	UPROPERTY()
		UMovementController* m_MovementController;

	UPROPERTY()
		ABasicCharacter* m_CharacterOwner;
};
