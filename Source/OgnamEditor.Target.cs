// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class OgnamEditorTarget : TargetRules
{
	public OgnamEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        //BuildEnvironment = TargetBuildEnvironment.Unique;

        ExtraModuleNames.AddRange( new string[] { "Ognam" } );
    }
}
