// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TokenizerT.h"

#include "utils/BertChineseTokenizer.h"

void UTokenizerT::BertChineseTokenizerTest()
{
	UBertChineseTokenizer* Tokenizer = NewObject<UBertChineseTokenizer>();
	Tokenizer->SetVocabMap();
}
