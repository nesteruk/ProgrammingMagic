#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include <memory>

class CardInPlay;

class Player
{
public:
  std::string Name;
  std::vector<Card*> Deck;
  std::vector<Card*> Sideboard;
  std::vector<Card*> Hand;
  std::vector<std::unique_ptr<CardInPlay>> CardsInPlay;
  std::vector<Card*> Graveyard, Exile;
};
