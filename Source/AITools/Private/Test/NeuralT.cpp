// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NeuralT.h"

#include "embedding/BertEmbeddingModel.h"


void UNeuralT::OnnxText()
{


	Ort::Env* Env = new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "UnrealONNX");

    // Load the ONNX model
    FString modelPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("AITools/Resources/onnx/bert-base-chinese.onnx"));
    Ort::SessionOptions sessionOptions;
    sessionOptions.SetIntraOpNumThreads(1);

    // Try to add CUDA execution provider
    //bool useGPU = false;
	//OrtSessionOptionsAppendExecutionProvider_CUDA(sessionOptions, 0);


    // Convert FString to std::wstring
    std::wstring modelPathWStr = std::wstring(*modelPath);
    const wchar_t* modelPathWChar = modelPathWStr.c_str();

    // Create the ONNX session
    Ort::Session* Session = new Ort::Session(*Env, modelPathWChar, sessionOptions);

    // Prepare input data
    // Prepare input data
	TArray<int64> inputIds = { 101,  1963,  3362,   809,  1184,  3766,  3300,  2970,  6239,  6814,
		  3322,  1690,  2110,   739,  2772,  5442,   100,  8024,  6821,   671,
		  3635,  1377,  5543,  7444,  6206,  5709,  4157,  3198,  7313,  1343,
		  3022,  2456,   100,  4384,  1862,  8024,   678,  7481,  3300,  1126,
		   702,  3152,  4995,  4638,  7216,  2970,   792,  5305,   749,   100,
		  4384,  1862,  3022,  2456,   809,  1350,   671,   763,  3322,  1690,
		  2110,   739,  1825,  4794,  8024,  1377,   809,  1346,  5440,  2110,
		   739,   671,   678,  8024,  2772,  5442,   677,   144,  4991,   677,
		  3017,  5164,  4685,  1068,  3136,  4923,   511,  3022,  2456,  2130,
		  2768,  1400,  2456,  6379,  1343, 10575,   677,  6651,  1126,   702,
		  4868,  5307,  5381,  5317,  4638,   100,  8024,  4225,  2634,   671,
		678,   511,  1963,  3362,   809,  1184,  3766,  3300,  2970,  6239,  6814,
	   3322,  1690,  2110,   739,  2772,  5442,   100,  8024,  6821,   671,
	   3635,  1377,  5543,  7444,  6206,  5709,  4157,  3198,  7313,  1343,
	   3022,  2456,   100,  4384,  1862,  8024,   678,  7481,  3300,  1126,
		702,  3152,  4995,  4638,  7216,  2970,   792,  5305,   749,   100,
	   4384,  1862,  3022,  2456,   809,  1350,   671,   763,  3322,  1690,
	   2110,   739,  1825,  4794,  8024,  1377,   809,  1346,  5440,  2110,
		739,   671,   678,  8024,  2772,  5442,   677,   144,  4991,   677,
	   3017,  5164,  4685,  1068,  3136,  4923,   511,  3022,  2456,  2130,
	   2768,  1400,  2456,  6379,  1343, 10575,   677,  6651,  1126,   702,
	   4868,  5307,  5381,  5317,  4638,   100,  8024,  4225,  2634,   671,
		678,   511,  1963,  3362,   809,  1184,  3766,  3300,  2970,  6239,  6814,
		  3322,  1690,  2110,   739,  2772,  5442,   100,  8024,  6821,   671,
		  3635,  1377,  5543,  7444,  6206,  5709,  4157,  3198,  7313,  1343,
		  3022,  2456,   100,  4384,  1862,  8024,   678,  7481,  3300,  1126,
		   702,  3152,  4995,  4638,  7216,  2970,   792,  5305,   749,   100,
		  4384,  1862,  3022,  2456,   809,  1350,   671,   763,  3322,  1690,
		  2110,   739,  1825,  4794,  8024,  1377,   809,  1346,  5440,  2110,
		   739,   671,   678,  8024,  2772,  5442,   677,   144,  4991,   677,
		  3017,  5164,  4685,  1068,  3136,  4923,   511,  3022,  2456,  2130,
		  2768,  1400,  2456,  6379,  1343, 10575,   677,  6651,  1126,   702,
		  4868,  5307,  5381,  5317,  4638,   100,  8024,  4225,  2634,   671,
		   678,   511,   102 }; // Example token IDs
	TArray<int64> attentionMask = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1}; // Example attention mask

    std::vector<int64_t> inputShape = { 1, static_cast<int64_t>(inputIds.Num()) };

    // Create input tensors
    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value inputIdsTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, inputIds.GetData(), inputIds.Num(), inputShape.data(), inputShape.size());
    Ort::Value attentionMaskTensor = Ort::Value::CreateTensor<int64_t>(memoryInfo, attentionMask.GetData(), attentionMask.Num(), inputShape.data(), inputShape.size());

    // Prepare input names and output names
    const char* inputNames[] = { "input_ids", "attention_mask" };
    const char* outputNames[] = { "output" };

    // Create a vector of input tensors
    std::vector<Ort::Value> inputTensors;
    inputTensors.push_back(std::move(inputIdsTensor));
    inputTensors.push_back(std::move(attentionMaskTensor));

	double BeginTime = FPlatformTime::Seconds();

    // Run the model
    auto outputTensors = Session->Run(Ort::RunOptions{ nullptr }, inputNames, inputTensors.data(), inputTensors.size(), outputNames, 1);

	for (int i=0;i<1000;i++)
	{
		outputTensors = Session->Run(Ort::RunOptions{ nullptr }, inputNames, inputTensors.data(), inputTensors.size(), outputNames, 1);

	}
	double EndTime=FPlatformTime::Seconds();
	UE_LOG(LogTemp,Warning,TEXT("bert run time:%f"),EndTime-BeginTime);
    // Get output data
    Ort::Value& outputTensor = outputTensors.front();
    float* outputData = outputTensor.GetTensorMutableData<float>();

    // Get output tensor shape
    Ort::TensorTypeAndShapeInfo outputInfo = outputTensor.GetTensorTypeAndShapeInfo();
    std::vector<int64_t> outputShape = outputInfo.GetShape();

    // Log output shape
    FString outputShapeStr;
    for (int64_t dim : outputShape)
    {
        outputShapeStr += FString::Printf(TEXT("%lld "), dim);
    }
    UE_LOG(LogTemp, Warning, TEXT("Output Shape: %s"), *outputShapeStr);

    // Extract [CLS] token embedding (first token)
    int64_t hiddenSize = outputShape[2];
    int64_t word_num = outputShape[1];
    float* clsEmbedding = outputData; // The first token's embedding

	// Log the [CLS] token embedding
	for (int64_t i = 0; i < hiddenSize * word_num; ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("CLS Embedding[%lld]: %f"), i, clsEmbedding[i]);
	}

	// Clean up
	delete Session;
	delete Env;
	
}

void UNeuralT::BertTest()
{
	UBertEmbeddingModel* BertEmbeddingModel=NewObject<UBertEmbeddingModel>();
	TArray<int64> inputIds = { 101,  1963,  3362,   809,  1184,  3766,  3300,  2970,  6239,  6814,
		  3322,  1690,  2110,   739,  2772,  5442,   100,  8024,  6821,   671,
		  3635,  1377,  5543,  7444,  6206,  5709,  4157,  3198,  7313,  1343,
		  3022,  2456,   100,  4384,  1862,  8024,   678,  7481,  3300,  1126,
		   702,  3152,  4995,  4638,  7216,  2970,   792,  5305,   749,   100,
		  4384,  1862,  3022,  2456,   809,  1350,   671,   763,  3322,  1690,
		  2110,   739,  1825,  4794,  8024,  1377,   809,  1346,  5440,  2110,
		   739,   671,   678,  8024,  2772,  5442,   677,   144,  4991,   677,
		  3017,  5164,  4685,  1068,  3136,  4923,   511,  3022,  2456,  2130,
		  2768,  1400,  2456,  6379,  1343, 10575,   677,  6651,  1126,   702,
		  4868,  5307,  5381,  5317,  4638,   100,  8024,  4225,  2634,   671,
		678,   511,  1963,  3362,   809,  1184,  3766,  3300,  2970,  6239,  6814,
	   3322,  1690,  2110,   739,  2772,  5442,   100,  8024,  6821,   671,
	   3635,  1377,  5543,  7444,  6206,  5709,  4157,  3198,  7313,  1343,
	   3022,  2456,   100,  4384,  1862,  8024,   678,  7481,  3300,  1126,
		702,  3152,  4995,  4638,  7216,  2970,   792,  5305,   749,   100,
	   4384,  1862,  3022,  2456,   809,  1350,   671,   763,  3322,  1690,
	   2110,   739,  1825,  4794,  8024,  1377,   809,  1346,  5440,  2110,
		739,   671,   678,  8024,  2772,  5442,   677,   144,  4991,   677,
	   3017,  5164,  4685,  1068,  3136,  4923,   511,  3022,  2456,  2130,
	   2768,  1400,  2456,  6379,  1343, 10575,   677,  6651,  1126,   702,
	   4868,  5307,  5381,  5317,  4638,   100,  8024,  4225,  2634,   671,
		678,   511,  1963,  3362,   809,  1184,  3766,  3300,  2970,  6239,  6814,
		  3322,  1690,  2110,   739,  2772,  5442,   100,  8024,  6821,   671,
		  3635,  1377,  5543,  7444,  6206,  5709,  4157,  3198,  7313,  1343,
		  3022,  2456,   100,  4384,  1862,  8024,   678,  7481,  3300,  1126,
		   702,  3152,  4995,  4638,  7216,  2970,   792,  5305,   749,   100,
		  4384,  1862,  3022,  2456,   809,  1350,   671,   763,  3322,  1690,
		  2110,   739,  1825,  4794,  8024,  1377,   809,  1346,  5440,  2110,
		   739,   671,   678,  8024,  2772,  5442,   677,   144,  4991,   677,
		  3017,  5164,  4685,  1068,  3136,  4923,   511,  3022,  2456,  2130,
		  2768,  1400,  2456,  6379,  1343, 10575,   677,  6651,  1126,   702,
		  4868,  5307,  5381,  5317,  4638,   100,  8024,  4225,  2634,   671,
		   678,   511,   102 }; // Example token IDs
	TArray<int64> attentionMask = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1}; // Example attention mask

	TArray<int32> Shape;
	Shape.Add(1);
	Shape.Add(attentionMask.Num());
	UTensor<int64> InputTensor_ID(Shape,inputIds);
	UTensor<int64> InputTensor_MASK(Shape,attentionMask);
	TArray<UTensor<int64>> InputData;
	InputData.Add(InputTensor_ID);
	InputData.Add(InputTensor_MASK);
	UTensor<float> OutputTensor;
	BertEmbeddingModel->Forward(InputData,OutputTensor);
	
}
