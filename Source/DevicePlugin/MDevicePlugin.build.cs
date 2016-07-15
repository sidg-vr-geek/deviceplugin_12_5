// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
    public class MDevicePlugin : ModuleRules
    {
        public MDevicePlugin(TargetInfo Target)
        {
            RulesAssembly r;
            FileReference CheckProjectFile;
            UProjectInfo.TryGetProjectForTarget("DeviceGame1", out CheckProjectFile);

            r = RulesCompiler.CreateProjectRulesAssembly(CheckProjectFile);
            FileReference f = r.GetModuleFileName(this.GetType().Name);
            //File.WriteAllText("c:/temp/qqq2.txt", f.CanonicalName );

            string ModulePath = Path.GetDirectoryName(f.CanonicalName);
            string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));

            PublicIncludePaths.AddRange(
                new string[]    {
                                    "../DevicePlugin/Public",
                                }
                );

            PrivateIncludePaths.AddRange(
                new string[]    {
                                    "../DevicePlugin/Private",
				                }
                );

            PublicDependencyModuleNames.AddRange(
                new string[]
				                {
					                "Core",
                                    "CoreUObject",
                                    "Engine"
				                }
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
				                {
				                }
                );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
				{
					// ... add any modules that your module loads dynamically here ...
				}
                );

            LoadDriverLibrary(Target, ModulePath, ThirdPartyPath);
        }

        public void LoadDriverLibrary(TargetInfo Target, string ModulePath, string ThirdPartyPath)
        {
            string LibrariesPath = Path.Combine(ThirdPartyPath, "DeviceDriver", "Libraries");
            string IncludesPath = Path.Combine(ThirdPartyPath, "DeviceDriver", "Includes");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DeviceDriverConsole32.lib"));
            PublicIncludePaths.Add(IncludesPath);
        }
    }
}