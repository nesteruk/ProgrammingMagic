#pragma once
#include "Player.h"

class Game
{
public:
  Player player, player2;

  std::vector<const CardInPlay*> GetCardsInPlay() const
  {
    std::vector<const CardInPlay*> result;
    for (auto& x : player.CardsInPlay)
      result.push_back(x.get());
    for (auto& x : player2.CardsInPlay)
      result.push_back(x.get());
    return result;
  }
};
