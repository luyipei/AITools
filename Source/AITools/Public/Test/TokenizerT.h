// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "TokenizerT.generated.h"

/**
 * 
 */
UCLASS()
class AITOOLS_API UTokenizerT : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	void BertChineseTokenizerTest();
};
