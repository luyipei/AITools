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
	
};

struct NetworkOutputData
{
	
};




UCLASS()
class AITOOLS_API UNeuralNetwork : public UObject
{
	GENERATED_BODY()

public:
	~UNeuralNetwork();
	
	void InitNetwork();

	void InitNetworkByModelPath(FString& Path);
	
	virtual void Forward(const NetworkInputData* InputData, NetworkOutputData* OutputData);

private:
	FString ModelPath=FString("");

	Ort::Env* Env;

	
	Ort::Session* Session;

	
	
};
