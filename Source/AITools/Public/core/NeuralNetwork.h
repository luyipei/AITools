// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "onnxruntime_cxx_api.h"
#include "NeuralNetwork.generated.h"

/**
 * 
 */


struct NetworkInputData
{
	virtual ~NetworkInputData() = default; // 添加虚析构函数
};

struct NetworkOutputData
{
	virtual ~NetworkOutputData() = default; // 添加虚析构函数
};




UCLASS()
class AITOOLS_API UNeuralNetwork : public UObject
{
	GENERATED_BODY()

public:
	~UNeuralNetwork();
	
	virtual void InitNetwork();

	virtual void InitNetworkByModelPath(FString& Path);
	
	virtual void Forward(const NetworkInputData* InputData, NetworkOutputData* OutputData);

private:
	FString ModelPath=FString("");

	Ort::Env* Env;

	
	Ort::Session* Session;

	
	
};
