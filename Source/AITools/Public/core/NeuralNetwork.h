// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "onnxruntime_cxx_api.h"
#include "NeuralNetwork.generated.h"

/**
 * 
 */


// 通用张量
template<typename T>
struct UTensor
{
	TArray<int32> Shape;  // 表示形状
	TArray<T> Value;      // 使用模板参数T来表示值的类型

	// 构造函数
	UTensor() {}

	UTensor(const TArray<int32>& InShape, const TArray<T>& InValue)
		: Shape(InShape), Value(InValue) {}

	// 获取张量的元素数量
	int32 GetNumElements() const
	{
		int32 NumElements = 1;
		for (int32 Dim : Shape)
		{
			NumElements *= Dim;
		}
		return NumElements;
	}

	// 检查张量的形状和值是否匹配
	bool IsValid() const
	{
		return GetNumElements() == Value.Num();
	}
};



UCLASS()
class AITOOLS_API UNeuralNetwork : public UObject
{
	GENERATED_BODY()

public:
	~UNeuralNetwork();
	
	virtual void InitNetwork();

	virtual void InitNetworkByModelPath(FString& Path);
	
	virtual void Forward(TArray<UTensor<double>>& InputData,UTensor<double>& OutputData);

	virtual void Forward(TArray<UTensor<int64>>& InputData,UTensor<float>& OutputData);



protected:
	FString ModelPath=FString("");

	Ort::Env* Env;

	
	Ort::Session* Session;

	
	
};
