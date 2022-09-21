// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HealthComp : ModuleRules
{
	public HealthComp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
