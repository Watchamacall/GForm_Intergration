// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GFormPlugin : ModuleRules
{
    public GFormPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Public dependencies - available to all modules including others linking to this one
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG", // Required for UUserWidget and related UI functionality
            "HTTP"  // For FGenericPlatformHttp and related functionality
        });

        // Private dependencies - internal use only
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate", // Slate UI framework
            "SlateCore" // Core functionality for Slate UI
        });

        // Uncomment if using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with Enabled set to true
    }
}