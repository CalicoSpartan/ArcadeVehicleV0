// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArcadeVehicleV0EditorTarget : TargetRules
{
	public ArcadeVehicleV0EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "ArcadeVehicleV0" } );
	}
}
