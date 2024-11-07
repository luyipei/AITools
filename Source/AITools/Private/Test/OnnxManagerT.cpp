// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/OnnxManagerT.h"


UOnnxManagerT& UOnnxManagerT::Get()
{
	static UOnnxManagerT Instance;
	return Instance;
}

UOnnxManagerT::UOnnxManagerT()
	: Env(nullptr), Session(nullptr)
{
	// Initialize ONNX Runtime
	//Env = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "UnrealONNX");

	// // Load the ONNX model
	// FString modelPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("AITool/Resources/onnx/bert-base-chinese.onnx"));
	// Ort::SessionOptions sessionOptions;
	// sessionOptions.SetIntraOpNumThreads(1);
	//
	// // Convert FString to const wchar_t*
	// const wchar_t* modelPathWChar = *modelPath;
	//
	// // Create the ONNX session
	// Session = new Ort::Session(*Env, modelPathWChar, sessionOptions);
}

UOnnxManagerT::~UOnnxManagerT()
{
	delete Session;
	delete Env;
}

void UOnnxManagerT::InitBertNetwork()
{
}
