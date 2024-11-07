// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tokenizer.h"
#include "BertChineseTokenizer.generated.h"

/**
 * 
 */
UCLASS()
class AITOOLS_API UBertChineseTokenizer : public UTokenizer
{
	GENERATED_BODY()
public:
	UBertChineseTokenizer();

	explicit UBertChineseTokenizer(const FString& Path);
	
	virtual void SetVocabMap() override;

	virtual void TokenizerTextProgress(FString Sentence,TArray<int>& InputIds,TArray<int>& InputMask) override;
};
