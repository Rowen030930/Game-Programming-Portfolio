// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U_ClaudPortf : ModuleRules
{
	public U_ClaudPortf(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
