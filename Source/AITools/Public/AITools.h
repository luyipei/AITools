// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAIToolsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
#pragma region 3DAsset
	

	TSharedRef<FExtender> ContentBrowserMenuAIToolsExtender(const TArray<FString>& SelectedPaths);

	void AIToolsExtension(FMenuBuilder& MenuBuilder);

	void Generate3DAsset();

#pragma endregion 3DAsset
};
