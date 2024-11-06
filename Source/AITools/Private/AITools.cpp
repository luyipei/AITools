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

	MenuBuilder.AddSubMenu(
		FText::FromString(TEXT("AIGC")), // Title text for the submenu
		FText::FromString(TEXT("Generate assets using AIGC")), // Tooltip text
		FNewMenuDelegate::CreateRaw(this, &FAIToolsModule::AddAIGCMenuEntries),
		false, // Default to false, meaning the submenu is not open by default
		FSlateIcon()
	);


	
	
	
}

void FAIToolsModule::AddAIGCMenuEntries(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry
	(
		FText::FromString(TEXT("generate 2d sprite")), //Title text for menu entry
		FText::FromString(TEXT("generate 2d sprite by aigc")), //Tooltip text
		FSlateIcon(),
		FExecuteAction::CreateRaw(this,&FAIToolsModule::Generate3DAsset)
		
	);

	MenuBuilder.AddMenuEntry
	(
		FText::FromString(TEXT("generate 3d asset")), //Title text for menu entry
		FText::FromString(TEXT("generate 3d asset by aigc")), //Tooltip text
		FSlateIcon(),
		FExecuteAction::CreateRaw(this,&FAIToolsModule::Generate3DAsset)
		
	);

	MenuBuilder.AddMenuEntry
	(
		FText::FromString(TEXT("generate 2d texture")), //Title text for menu entry
		FText::FromString(TEXT("generate 2d texture by aigc")), //Tooltip text
		FSlateIcon(),
		FExecuteAction::CreateRaw(this,&FAIToolsModule::Generate3DAsset)
	);
	
}


void FAIToolsModule::Generate3DAsset()
{
	//弹出来unreal editor的对话框，提示输入提示词，然后点击确定或者取消
	// 创建一个对话框窗口
    TSharedRef<SWindow> DialogWindow = SNew(SWindow)
        .Title(FText::FromString("Input Prompt"))
        .ClientSize(FVector2D(400, 200))
        .SupportsMinimize(false)
        .SupportsMaximize(false);

    // 创建一个文本框，用于输入提示词
    TSharedPtr<SEditableTextBox> InputTextBox;
    DialogWindow->SetContent(
        SNew(SBox)
        .WidthOverride(350)
        .HeightOverride(150)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .Padding(10)
            .AutoHeight()
            [
                SNew(STextBlock)
                .Text(FText::FromString("Please enter the prompt:"))
            ]
            + SVerticalBox::Slot()
            .Padding(10)
            .AutoHeight()
            [
                SAssignNew(InputTextBox, SEditableTextBox)
            ]
            + SVerticalBox::Slot()
            .Padding(10)
            .AutoHeight()
            .HAlign(HAlign_Right)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(5, 0)
                [
                    SNew(SButton)
                    .Text(FText::FromString("OK"))
                    .OnClicked_Lambda([this,DialogWindow, InputTextBox]()
                    {
                        // 获取输入的提示词
                        FString Prompt = InputTextBox->GetText().ToString();
                        // 在这里处理提示词
                        this->Generate3DAssetProgress(Prompt);

                        // 关闭对话框
                        DialogWindow->RequestDestroyWindow();
                        return FReply::Handled();
                    })
                ]
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(5, 0)
                [
                    SNew(SButton)
                    .Text(FText::FromString("Cancel"))
                    .OnClicked_Lambda([DialogWindow]()
                    {
                        // 关闭对话框
                        DialogWindow->RequestDestroyWindow();
                        return FReply::Handled();
                    })
                ]
            ]
        ]
    );

    // 显示对话框
    FSlateApplication::Get().AddWindow(DialogWindow);
}

void FAIToolsModule::Generate3DAssetProgress(const FString& Prompt)
{
	UE_LOG(LogTemp, Log, TEXT("Prompt: %s"), *Prompt);
	//TODO
	
}

#pragma endregion 3DAsset


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAIToolsModule, AITools)