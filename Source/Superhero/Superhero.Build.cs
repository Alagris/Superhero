// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class Superhero : ModuleRules
{
    private string PluginsPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Plugins/")); }
    }

    protected void AddSPUD()
    {
        // Linker
        PrivateDependencyModuleNames.AddRange(new string[] { "SPUD" });
        // Headers
        PublicIncludePaths.Add(Path.Combine(PluginsPath, "SPUD", "Source", "SPUD", "Public"));
    }

    public Superhero(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
            "AnimGraphRuntime",
            "UMG",
            "SlateCore",
            "Slate",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Superhero",
			"Superhero/Variant_Strategy",
			"Superhero/Variant_Strategy/UI",
			"Superhero/Variant_TwinStick",
			"Superhero/Variant_TwinStick/AI",
			"Superhero/Variant_TwinStick/Gameplay",
			"Superhero/Variant_TwinStick/UI"
		});

        AddSPUD();
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
