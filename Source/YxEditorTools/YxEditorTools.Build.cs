// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class YxEditorTools : ModuleRules
{
	public YxEditorTools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore",
				"EditorFramework",
				"UnrealEd",
				"PropertyEditor",
			}
		);
		
	}
}
