// Fill out your copyright notice in the Description page of Project Settings.


#include "embedding/BertEmbeddingModel.h"

void UBertEmbeddingModel::Forward(const NetworkInputData* InputData, NetworkOutputData* OutputData)
{
	// Prepare input data
    // TArray<int64> inputIds = { 101, 6821, 3221,  671,  702, 4850,  891, 3152, 3315,  511,  102 }; // Example token IDs
    // TArray<int64> attentionMask = { 1, 1, 1, 1, 1, 1,1,1,1,1,1 }; // Example attention mask
	//TArray<int64>& inputIds=InputData->
	// BertInputData* bertInputData=dynamic_cast<BertInputData*>(InputData);
	// if (bertInputData)
	// {
	// 	TArray<int64>& inputIds = bertInputData->InputIds;
	// 	TArray<int64> attentionMask=bertInputData->AttentionMask;
	//
	// 	std::vector<int64_t> inputShape = { 1, static_cast<int64_t>(inputIds.Num()) };
	//
	// 	// Create input tensors
	// 	Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
	// 	Ort::Value inputIdsTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, inputIds.GetData(), inputIds.Num(), inputShape.data(), inputShape.size());
	// 	Ort::Value attentionMaskTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, attentionMask.GetData(), attentionMask.Num(), inputShape.data(), inputShape.size());
	//
	// 	// Prepare input names and output names
	// 	const char* inputNames[] = { "input_ids", "attention_mask" };
	// 	const char* outputNames[] = { "output" };
	//
	// 	// Create a vector of input tensors
	// 	std::vector<Ort::Value> inputTensors;
	// 	inputTensors.push_back(std::move(inputIdsTensor));
	// 	inputTensors.push_back(std::move(attentionMaskTensor));
	//
	// 	// Run the model
	// 	auto outputTensors = Session->Run(Ort::RunOptions{ nullptr }, inputNames, inputTensors.data(), inputTensors.size(), outputNames, 1);
	//
	// 	// Get output data
	// 	Ort::Value& outputTensor = outputTensors.front();
	// 	float* outputData = outputTensor.GetTensorMutableData<float>();
	//
	// 	// Get output tensor shape
	// 	Ort::TensorTypeAndShapeInfo outputInfo = outputTensor.GetTensorTypeAndShapeInfo();
	// 	std::vector<int64_t> outputShape = outputInfo.GetShape();
	//
	// 	// Log output shape
	// 	FString outputShapeStr;
	// 	for (int64_t dim : outputShape)
	// 	{
	// 		outputShapeStr += FString::Printf(TEXT("%lld "), dim);
	// 	}
	// 	UE_LOG(LogTemp, Warning, TEXT("Output Shape: %s"), *outputShapeStr);
	//
	// 	// Extract [CLS] token embedding (first token)
	// 	int64_t hiddenSize = outputShape[2];
	//
	// 	int64_t word_num= outputShape[1];
	// 	float* clsEmbedding = outputData; // The first token's embedding
	//
	// 	// Log the [CLS] token embedding
	// 	for (int64_t i = 0; i < hiddenSize*word_num; ++i)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("CLS Embedding[%lld]: %f"), i, clsEmbedding[i]);
	// 	}
	// }
	

    
}
