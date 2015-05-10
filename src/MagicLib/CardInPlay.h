#pragma once
#include "Card.h"
#include <functional>
#include "Game.h"
#include "GameContext.h"

class CardInPlay
{
  const Game& game;
  std::unique_ptr<GameContext> GetContext() const
  {
    auto ctx = std::make_unique<GameContext>(game, Archetype);
    for (auto cipp : game.GetCardsInPlay())
      for (auto& affect : cipp->Affects)
        affect(*ctx);
    return ctx;
  }
public:
  uint64_t Uid;
  CardInPlay(const Game& game, const Card& archetype)
    : game(game),
      Archetype(archetype)
  {
    static uint64_t seed = 0;
    Uid = seed++;
  }

  const Card& Archetype;
  std::vector<std::function<void(GameContext&)>> Affects;

  int GetPower() const
  {
    return GetContext()->Card.Power;
  }
  __declspec(property(get = GetPower)) int Power;

  int GetToughness() const
  {
    return GetContext()->Card.Toughness;
  }
  __declspec(property(get = GetToughness)) int Toughness;
};
