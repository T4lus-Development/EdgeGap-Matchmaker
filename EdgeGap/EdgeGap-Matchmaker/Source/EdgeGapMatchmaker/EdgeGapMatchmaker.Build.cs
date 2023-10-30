// Some copyright should be here...

using UnrealBuildTool;

public class EdgeGapMatchmaker : ModuleRules
{
	public EdgeGapMatchmaker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        /*
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public/Core"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public/Matchmaker"));

        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Core"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Matchmaker"));
        */

        PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
                "CoreUObject",
            }
		);

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "HTTP",
                "Json",
                "JsonUtilities"
            }
        );
    }
}
