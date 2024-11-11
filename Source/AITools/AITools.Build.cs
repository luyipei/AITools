// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class AITools : ModuleRules
{
	public AITools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// 获取插件目录
		string PluginPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../"));

		// 添加 ONNX Runtime 的头文件路径
		PublicIncludePaths.Add(Path.Combine(PluginPath, "ThirdParty", "onnxruntime", "include"));

		// 添加 ONNX Runtime 的库文件路径
		PublicAdditionalLibraries.Add(Path.Combine(PluginPath, "ThirdParty", "onnxruntime", "lib", "onnxruntime.lib"));
		RuntimeDependencies.Add(Path.Combine(PluginPath, "ThirdParty", "onnxruntime", "lib", "onnxruntime_providers_cuda.lib"));
		
		
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				Path.Combine(ModuleDirectory, "ThirdParty", "onnxruntime", "include")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				//Path.Combine(ModuleDirectory, "ThirdParty", "onnxruntime", "lib", "onnxruntime.lib")
			}
			);
		
		// 添加公共DLL路径
		//PublicDelayLoadDLLs.Add("onnxruntime.dll");

		// 确保DLL在运行时被复制到输出目录
		RuntimeDependencies.Add("$(BinaryOutputDir)/onnxruntime.dll", Path.Combine(PluginPath, "ThirdParty", "onnxruntime", "lib",  "onnxruntime.dll"));
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
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
				"EditorSubsystem",
				"UnrealEd" // 添加这一行
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
