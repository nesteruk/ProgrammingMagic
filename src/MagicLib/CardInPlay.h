#pragma once
#include "Card.h"
#include <functional>
#include "Game.h"
#include "GameContext.h"

class CardInPlay : public Target
{
  const Game& game;
  std::unique_ptr<GameContext> GetContext() const
  {
    auto ctx = std::make_unique<GameContext>(game, Archetype);
    for (auto cipp : game.GetCardsInPlay())
      for (auto& affect : cipp->Archetype.Affects)
        affect(*ctx);
    return ctx;
  }
  static uint64_t seed;
public:
  const uint64_t Uid;
  CardInPlay(const Game& game, const Card& archetype)
    : game(game)
    , Uid(seed++)
	, Archetype(archetype)
  {
  }

  const Card& Archetype;

  Mana GetCost() const
  {
	  return GetContext()->Card.ManaCost;
  }
  __declspec(property(get = GetCost)) Mana ManaCost;

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
