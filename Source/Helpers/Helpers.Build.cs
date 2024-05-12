using UnrealBuildTool;
 
public class Helpers: ModuleRules
{
	public Helpers(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"TraceLog",
				"CoreUObject",
				"Engine",
				"InputCore",
				"Slate",
				"SlateCore",
				"UMG",
				"EnhancedInput",
				"Playground"
			}
		);
	}
}