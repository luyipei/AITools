// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tokenizer.generated.h"

/**
 * 
 */
UCLASS()
class AITOOLS_API UTokenizer : public UObject
{
	GENERATED_BODY()

public:
	void TokenizerText(FString Sentence,TArray<int>& InputIds,TArray<int>& InputMask);

	virtual void TokenizerTextProgress(FString Sentence,TArray<int>& InputIds,TArray<int>& InputMask);

	virtual void SetVocabMap();

protected:
	// FVector InputIDs;
	// FVector InputMask;
	TMap<FString,int> VocabMap;
	FString VocabPath;
	bool VocabMapVaild=false;
};
