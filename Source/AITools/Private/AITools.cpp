// Copyright Epic Games, Inc. All Rights Reserved.

#include "AITools.h"

#include "ContentBrowserModule.h"


#define LOCTEXT_NAMESPACE "FAIToolsModule"

void FAIToolsModule::StartupModule()
{

	UE_LOG(LogTemp, Warning, TEXT("AITools Module Start"));
	FContentBrowserModule& ContentBrowserModule =
	FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	/*
	 *特别注意！！！
	 *这里要用引用，不然是没有修改原来的extenders的值的
	 */
	TArray<FContentBrowserMenuExtender_SelectedPaths>& AssetContextMenuExtenders = ContentBrowserModule.GetAllAssetContextMenuExtenders();
	FContentBrowserMenuExtender_SelectedPaths ContentBrowserMenuExtender_SelectedPaths_AITools;
	ContentBrowserMenuExtender_SelectedPaths_AITools.BindRaw(this,&FAIToolsModule::ContentBrowserMenuAIToolsExtender);
	AssetContextMenuExtenders.Add(ContentBrowserMenuExtender_SelectedPaths_AITools);
	
}

void FAIToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}


#pragma region 3DAsset

TSharedRef<FExtender> FAIToolsModule::ContentBrowserMenuAIToolsExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> MenuExtender(new FExtender());
	if(SelectedPaths.Num()>0)
	{
		MenuExtender->AddMenuExtension(FName("ContentBrowserNewAdvancedAsset"), //Extend hook, position to insert
		EExtensionHook::After, //Insert before or after
		TSharedPtr<FUICommandList>(), //Custom hot keys
		FMenuExtensionDelegate::CreateRaw(this,&FAIToolsModule::AIToolsExtension)
		); //Second binding, will define details for this menu entry

	}
	
	return  MenuExtender;
}

void FAIToolsModule::AIToolsExtension(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry
	(
		FText::FromString(TEXT("generate 3d asset")), //Title text for menu entry
		FText::FromString(TEXT("generate 3d asset by aigc")), //Tooltip text
		FSlateIcon(),
		FExecuteAction::CreateRaw(this,&FAIToolsModule::Generate3DAsset)
		
	);
}


void FAIToolsModule::Generate3DAsset()
{
}

#pragma endregion 3DAsset


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAIToolsModule, AITools)