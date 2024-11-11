// Fill out your copyright notice in the Description page of Project Settings.


#include "embedding/BertEmbeddingModel.h"

void UBertEmbeddingModel::Forward(TArray<UTensor<int64>>& InputData, UTensor<float>& OutputData)
{
	InitNetwork();
	if (InputData.Num()>=2)
	{
		UTensor<int64>& inputIds=InputData[0];
		UTensor<int64>& attentionMask=InputData[1];

		std::vector<int64_t> inputShape = { 1, static_cast<int64_t>(inputIds.GetNumElements()) };

		// Create input tensors
		Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
		Ort::Value inputIdsTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, inputIds.Value.GetData(), inputIds.Value.Num(), inputShape.data(), inputShape.size());
		Ort::Value attentionMaskTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, attentionMask.Value.GetData(), attentionMask.Value.Num(), inputShape.data(), inputShape.size());

		// 
		const char* inputNames[] = { "input_ids", "attention_mask" };
		const char* outputNames[] = { "output" };

		// Create a vector of input tensors
		std::vector<Ort::Value> inputTensors;
		inputTensors.push_back(std::move(inputIdsTensor));
		inputTensors.push_back(std::move(attentionMaskTensor));

		double BeginTime = FPlatformTime::Seconds();

		// Run the model
		auto outputTensors = Session->Run(Ort::RunOptions{ nullptr }, inputNames, inputTensors.data(), inputTensors.size(), outputNames, 1);
		double EndTime=FPlatformTime::Seconds();
		UE_LOG(LogTemp,Warning,TEXT("bert run time:%f"),EndTime-BeginTime);

		Ort::Value& outputTensor = outputTensors.front();
		float* outputData = outputTensor.GetTensorMutableData<float>();

		// Get output tensor shape
		Ort::TensorTypeAndShapeInfo outputInfo = outputTensor.GetTensorTypeAndShapeInfo();
		std::vector<int64_t> outputShape = outputInfo.GetShape();

		OutputData.Shape.Empty();
		for(auto dim:outputShape)
		{
			OutputData.Shape.Add(dim);
		}
		
		// Extract [CLS] token embedding (first token)
		int64_t hiddenSize = outputShape[2];
		int64_t word_num = outputShape[1];
		float* clsEmbedding = outputData; // The first token's embedding
		for (int64_t i = 0; i < hiddenSize * word_num; ++i)
		{
			OutputData.Value.Add(clsEmbedding[i]);
		}
	}
}

void UBertEmbeddingModel::Forward(TArray<UTensor<double>>& InputData, UTensor<double>& OutputData)
{
}
