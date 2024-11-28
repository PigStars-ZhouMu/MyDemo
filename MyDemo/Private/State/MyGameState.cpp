// Fill out your copyright notice in the Description page of Project Settings.


#include "State/MyGameState.h"

void AMyGameState::AddScore(APlayerController* Player, int32 Score)
{
	if (Player) {
		if (PlayerScores.Contains(Player)) {
			PlayerScores[Player] += Score;
		}
		else {
			PlayerScores.Add(Player, Score);
		}
		UE_LOG(LogTemp, Warning, TEXT("Player %s now has %d points"), *Player->GetName(), PlayerScores[Player]);
	}
}


