// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "onnxruntime_cxx_api.h"

#include "NeuralT.generated.h"

/**
 * 
 */
UCLASS()
class AITOOLS_API UNeuralT : public UObject
{
	GENERATED_BODY()
public:

	void OnnxText();
};
