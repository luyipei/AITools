// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <onnxruntime_cxx_api.h>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OnnxManagerT.generated.h"

/**
 * 
 */
UCLASS()
class AITOOLS_API UOnnxManagerT : public UObject
{
	GENERATED_BODY()

public:
	static UOnnxManagerT& Get();
	void InitBertNetwork();

private:
	UOnnxManagerT();
	~UOnnxManagerT();

	Ort::Env* Env;
	Ort::Session* Session;
};
