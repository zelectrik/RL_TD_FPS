// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraShake.h"

UMyCameraShake::UMyCameraShake()
{
	OscillationBlendInTime = 0.01f;
	OscillationBlendOutTime = 0.01f;
	
	OscillationDuration = 0.03f;

	RotOscillation.Pitch.Amplitude = FMath::RandRange(0.1f, 0.3f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(1.0f,3.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(0.1f, 0.3f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(1.0f, 3.0f);
}
