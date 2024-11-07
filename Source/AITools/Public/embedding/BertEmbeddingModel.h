// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "core/NeuralNetwork.h"
#include "BertEmbeddingModel.generated.h"



/**
 * 
 */

struct BertInputData : public NetworkInputData
{
	
};

struct BertOutputData : public NetworkOutputData
{
	
};
UCLASS()
class AITOOLS_API UBertEmbeddingModel : public UNeuralNetwork
{
	GENERATED_BODY()

public:
	virtual void Forward(const NetworkInputData* InputData, NetworkOutputData* OutputData) override;
};
