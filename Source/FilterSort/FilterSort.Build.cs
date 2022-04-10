// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FilterSort : ModuleRules
{
	public FilterSort(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(new string[]
		{
			ModuleDirectory + "/Private",
			ModuleDirectory + "/Public",
			ModuleDirectory + "/Public/Filter",
			ModuleDirectory + "/Public/Sort",
			ModuleDirectory + "/Public/Widget/Filter",
		});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "UMG",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
	}
}
