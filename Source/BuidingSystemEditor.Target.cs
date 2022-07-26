// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BuidingSystemEditorTarget : TargetRules
{
	public BuidingSystemEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BuidingSystem" } );
		BuildEnvironment = TargetBuildEnvironment.Shared;
		bCompileChaos = true;
		bUseChaos = true;

	}
}
