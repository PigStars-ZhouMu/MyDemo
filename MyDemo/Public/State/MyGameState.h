// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYDEMO_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	TMap<APlayerController*, int32> PlayerScores;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(APlayerController* Player, int32 Score);
};
