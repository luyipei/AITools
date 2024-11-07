// Fill out your copyright notice in the Description page of Project Settings.


#include "utils/Tokenizer.h"

void UTokenizer::TokenizerText(FString Sentence, TArray<int>& InputIds, TArray<int>& InputMask)
{
	if (!VocabMapVaild)
	{
		SetVocabMap();
	}
	TokenizerTextProgress(Sentence, InputIds, InputMask);
}

void UTokenizer::SetVocabMap()
{
}

void UTokenizer::TokenizerTextProgress(FString Sentence, TArray<int>& InputIds, TArray<int>& InputMask)
{
}
