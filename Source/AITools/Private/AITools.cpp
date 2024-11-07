// Copyright Epic Games, Inc. All Rights Reserved.

#include "AITools.h"

#include "ContentBrowserModule.h"
#include "onnxruntime_cxx_api.h"
#include "Test/OnnxManagerT.h"
#include "Test/TokenizerT.h"


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

	OnnxTest();
	
	
}

void FAIToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FAIToolsModule::OnnxTest()
{

	Ort::Env* Env = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "UnrealONNX");

    // Load the ONNX model
    FString modelPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("AITools/Resources/onnx/bert-base-chinese.onnx"));
    Ort::SessionOptions sessionOptions;
    sessionOptions.SetIntraOpNumThreads(1);

    // Convert FString to std::wstring
    std::wstring modelPathWStr = std::wstring(*modelPath);
    const wchar_t* modelPathWChar = modelPathWStr.c_str();

    // Create the ONNX session
    Ort::Session* Session = new Ort::Session(*Env, modelPathWChar, sessionOptions);

    // Prepare input data
    TArray<int64> inputIds = { 101, 6821, 3221,  671,  702, 4850,  891, 3152, 3315,  511,  102 }; // Example token IDs
    TArray<int64> attentionMask = { 1, 1, 1, 1, 1, 1,1,1,1,1,1 }; // Example attention mask

    std::vector<int64_t> inputShape = { 1, static_cast<int64_t>(inputIds.Num()) };

    // Create input tensors
    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value inputIdsTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, inputIds.GetData(), inputIds.Num(), inputShape.data(), inputShape.size());
    Ort::Value attentionMaskTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, attentionMask.GetData(), attentionMask.Num(), inputShape.data(), inputShape.size());

    // Prepare input names and output names
    const char* inputNames[] = { "input_ids", "attention_mask" };
    const char* outputNames[] = { "output" };

    // Create a vector of input tensors
    std::vector<Ort::Value> inputTensors;
    inputTensors.push_back(std::move(inputIdsTensor));
    inputTensors.push_back(std::move(attentionMaskTensor));

    // Run the model
    auto outputTensors = Session->Run(Ort::RunOptions{ nullptr }, inputNames, inputTensors.data(), inputTensors.size(), outputNames, 1);

    // Get output data
    Ort::Value& outputTensor = outputTensors.front();
    float* outputData = outputTensor.GetTensorMutableData<float>();

    // Get output tensor shape
    Ort::TensorTypeAndShapeInfo outputInfo = outputTensor.GetTensorTypeAndShapeInfo();
    std::vector<int64_t> outputShape = outputInfo.GetShape();

    // Log output shape
    FString outputShapeStr;
    for (int64_t dim : outputShape)
    {
        outputShapeStr += FString::Printf(TEXT("%lld "), dim);
    }
    UE_LOG(LogTemp, Warning, TEXT("Output Shape: %s"), *outputShapeStr);

	// Extract [CLS] token embedding (first token)
	int64_t hiddenSize = outputShape[2];

	int64_t word_num= outputShape[1];
	float* clsEmbedding = outputData; // The first token's embedding

	// Log the [CLS] token embedding
	for (int64_t i = 0; i < hiddenSize*word_num; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("CLS Embedding[%lld]: %f"), i, clsEmbedding[i]);
	}

    // Process output data
    // for (int64_t i = 0; i < outputShape[1]; ++i)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Output[%lld]: %f"), i, outputData[i]);
    // }

    // Clean up
    delete Session;
    delete Env;
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