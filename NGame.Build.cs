// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NGame : ModuleRules
{
	public NGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { "CinematicCamera", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
    }
}
