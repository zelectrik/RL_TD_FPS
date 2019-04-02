// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Public/UObject/ConstructorHelpers.h"
#include "Public/Misc/MessageDialog.h"
#include "BaseWeapon.generated.h"

class ABasicPlayerController;

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class E_OnFireResult : uint8
{
	VE_Success		UMETA(DisplayName = "Success"),
	VE_NoAmmo		UMETA(DisplayName = "NoAmmo"),
	VE_FireRateNotReady	UMETA(DisplayName = "FireRateNotReady")
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class E_OnReloadResult : uint8
{
	VE_Success		UMETA(DisplayName = "Success"),
	VE_MaxAmmo		UMETA(DisplayName = "MaxAmmo"),
	VE_NoAmmoRemaining	UMETA(DisplayName = "NoAmmoRemaining")
};

UCLASS()
class RL_TD_FPS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* m_WeaponMesh;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual E_OnFireResult Fire();

	virtual void StopFire();

	virtual E_OnReloadResult Reload();

protected:

	UFUNCTION()
		ABasicPlayerController* GetCharacterController();

	UPROPERTY()
		float m_SightDistance;

	


	FVector GetBulletDirection();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	UFUNCTION()
		void SetCharacterController(ABasicPlayerController* _controller);
private:
	UPROPERTY()
		bool b_CanShoot;

	UPROPERTY()
		bool b_IsShooting;

	UPROPERTY()
		ABasicPlayerController* m_CharacterController;


};
