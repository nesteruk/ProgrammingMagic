#pragma once
#include "Player.h"
#include "Target.h"

class Game
{
public:
  Player player, player2;

	vector<Target*> GetTargets() const;

	vector<CardInPlay*> GetCardsInPlay() const;
};
