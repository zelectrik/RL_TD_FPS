// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class RL_TD_FPSEditorTarget : TargetRules
{
	public RL_TD_FPSEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "RL_TD_FPS" } );
	}
}
