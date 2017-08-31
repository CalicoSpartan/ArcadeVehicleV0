// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ArcadeVehicleV0Target : TargetRules
{
	public ArcadeVehicleV0Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "ArcadeVehicleV0" } );
	}
}
