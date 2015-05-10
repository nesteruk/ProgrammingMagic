#pragma once
#include "Card.h"

class GameContext
{
public:
  const Game& Game;
  Card Card;

  GameContext(const ::Game& game, ::Card card)
    : Game(game),
      Card(card)
  {
  }
};
