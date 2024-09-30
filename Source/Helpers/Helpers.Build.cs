using UnrealBuildTool;
 
public class Helpers: ModuleRules
{
	public Helpers(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] {
			"Playground"
			}
		);

		PrivateDependencyModuleNames.AddRange( new string[]  {
			"Core",
			"TraceLog",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			"UMG",
			"EnhancedInput"
			}
		);
}
}