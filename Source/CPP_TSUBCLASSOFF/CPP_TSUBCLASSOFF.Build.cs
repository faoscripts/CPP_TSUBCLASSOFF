// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPP_TSUBCLASSOFF : ModuleRules
{
	public CPP_TSUBCLASSOFF(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
