// Fill out your copyright notice in the Description page of Project Settings.


#include "utils/BertChineseTokenizer.h"

UBertChineseTokenizer::UBertChineseTokenizer()
{
	VocabPath = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("AITools/Resources/tokenizer/bert_vocab.txt"));
	//SetVocabMap();
	
}

UBertChineseTokenizer::UBertChineseTokenizer(const FString& Path)
{
	VocabPath=Path;
}

void UBertChineseTokenizer::SetVocabMap()
{
	// 确保文件存在
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*VocabPath))
	{
		UE_LOG(LogTemp, Error, TEXT("Vocab file not found: %s"), *VocabPath);
		return;
	}
	// 读取文件内容
	TArray<FString> FileLines;
	if (FFileHelper::LoadFileToStringArray(FileLines, *VocabPath))
	{
		for (int32 LineNumber = 0; LineNumber < FileLines.Num(); ++LineNumber)
		{
			FString Line = FileLines[LineNumber];
			VocabMap.Add(Line, LineNumber);
		}

		UE_LOG(LogTemp, Log, TEXT("vocab file loaded successfully."));
		// 输出前十行
		// int32 Count = 0;
		// for (const TPair<FString, int32>& Pair : VocabMap)
		// {
		// 	if (Count >= 10)
		// 	{
		// 		break;
		// 	}
		//
		// 	UE_LOG(LogTemp, Log, TEXT("Line %d: %s"), Pair.Value, *Pair.Key);
		// 	Count++;
		// }
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load vocab file: %s"), *VocabPath);
	}
	
}

void UBertChineseTokenizer::TokenizerTextProgress(FString Sentence, TArray<int>& InputIds, TArray<int>& InputMask)
{
	// 清空输入数组
	InputIds.Empty();
	InputMask.Empty();

	// 分词
	TArray<FString> Tokens;
	// Sentence.ParseIntoArray(Tokens, TEXT(" "), true);
	
	for (int32 i = 0; i < Sentence.Len(); i++)
	{
		FString Character = FString(1, &Sentence[i]);
		Tokens.Add(Character);
	}

	// 将 [CLS] token 添加到开头
	InputIds.Add(VocabMap["[CLS]"]);
	InputMask.Add(1);

	// 遍历每个 token 并添加到 InputIds 和 InputMask
	for (const FString& Token : Tokens)
	{
		if (VocabMap.Contains(Token))
		{
			InputIds.Add(VocabMap[Token]);
			InputMask.Add(1);
		}
		else
		{
			// 如果 token 不在词汇表中，使用 [UNK] token
			InputIds.Add(VocabMap["[UNK]"]);
			InputMask.Add(1);
		}
	}

	// 将 [SEP] token 添加到结尾
	InputIds.Add(VocabMap["[SEP]"]);
	InputMask.Add(1);
}
