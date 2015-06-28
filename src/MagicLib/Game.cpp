#include "stdafx.h"
#include "Target.h"
#include "CardInPlay.h"
#include "Game.h"

vector<Target*> Game::GetTargets() const
{
	vector<Target*> result;
	for (CardInPlay* cip : GetCardsInPlay())
	{
    result.push_back(cip);
	}

	return result;
}

vector<CardInPlay*> Game::GetCardsInPlay() const
{
	vector<CardInPlay*> result;
	for (auto& x : player.CardsInPlay)
		result.push_back(x.get());
	for (auto& x : player2.CardsInPlay)
		result.push_back(x.get());
	return result;
}