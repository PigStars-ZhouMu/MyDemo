// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyDemoGameMode.generated.h"


UCLASS(minimalapi)
class AMyDemoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyDemoGameMode();

	UFUNCTION(BlueprintCallable, Category = "TimeUp")
	void OnGameTimeUp();

	//virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameRule")
	int NumberOfImportantCube = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameRule")
	float GameLifetime = 30.0f;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle GameTimerHandle;
};



