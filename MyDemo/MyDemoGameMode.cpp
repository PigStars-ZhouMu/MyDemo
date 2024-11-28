// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyDemoGameMode.h"
#include "MyDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/World.h"
#include "State/MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "MyActor/Cube.h"

AMyDemoGameMode::AMyDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
    GameStateClass = AMyGameState::StaticClass();


	//UE_LOG(LogTemp, Warning, TEXT("GameMode Constructor"));
}

void AMyDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

    // Get all Cube
    TArray<ACube*> Cubes;
    for (TActorIterator<ACube> It(GetWorld()); It; ++It)
    {
        ACube* Cube = *It;
        if (Cube)
        {
            Cubes.Add(Cube);
        }
    }

	// Set n cubes is important target
    for (int32 i = 0; i < NumberOfImportantCube && Cubes.Num() > 0; ++i)
    {
        int32 Index = FMath::RandRange(0, Cubes.Num() - 1);
        ACube* ImportantCube = Cubes[Index];
        ImportantCube->bIsImportantTarget = true;
        ImportantCube->SetColor(FLinearColor::Red);
        Cubes.RemoveAt(Index);
    }

    GetWorld()->GetTimerManager().SetTimer(GameTimerHandle, this, &AMyDemoGameMode::OnGameTimeUp, GameLifetime, false);
}

void AMyDemoGameMode::OnGameTimeUp()
{   
    UE_LOG(LogTemp, Warning, TEXT("Time Up!"));

    if (AMyGameState* MyGameState = GetGameState<AMyGameState>())
    {
        int32 TotalScore = 0;
        for (const auto& PlayerScorePair : MyGameState->PlayerScores)
        {
            APlayerController* Player = PlayerScorePair.Key;
            int32 PlayerScore = PlayerScorePair.Value;
            TotalScore += PlayerScore;

            UE_LOG(LogTemp, Warning, TEXT("Player %s scored: %d"), *Player->GetName(), PlayerScore);
        }

        UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
    }

    // 结束游戏的逻辑，例如重新加载当前关卡
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}