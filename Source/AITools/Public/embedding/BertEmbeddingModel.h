// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "core/NeuralNetwork.h"
#include "BertEmbeddingModel.generated.h"



/**
 * 
 */


UCLASS()
class AITOOLS_API UBertEmbeddingModel : public UNeuralNetwork
{
	GENERATED_BODY()

public:
	virtual void Forward(TArray<UTensor<double>>& InputData, UTensor<double>& OutputData) override;

	virtual void Forward(TArray<UTensor<int64>>& InputData, UTensor<float>& OutputData) override;
};
