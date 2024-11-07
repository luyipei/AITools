// Fill out your copyright notice in the Description page of Project Settings.


#include "core/NeuralNetwork.h"

void UNeuralNetwork::InitNetwork()
{
	if (ModelPath==FString(""))
	{
		ModelPath=FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("AITools/Resources/onnx/bert-base-chinese.onnx"));
	}
	Env = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "UnrealONNX");
	Ort::SessionOptions SessionOptions;
	SessionOptions.SetIntraOpNumThreads(1);
	// Convert FString to std::wstring
	std::wstring modelPathWStr = std::wstring(*ModelPath);
	const wchar_t* modelPathWChar = modelPathWStr.c_str();

	// Create the ONNX session
	Session = new Ort::Session(*Env, modelPathWChar,SessionOptions);
}

void UNeuralNetwork::InitNetworkByModelPath(FString& Path)
{
	ModelPath=Path;
	InitNetwork();
}

void UNeuralNetwork::Forward(const NetworkInputData* InputData, NetworkOutputData* OutputData)
{
}

UNeuralNetwork::~UNeuralNetwork()
{
	delete Env;
	delete Session;
}
