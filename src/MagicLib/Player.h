#pragma once
#include "Card.h"
#include "Target.h"

class CardInPlay;

class Player : public Target
{
public:
  string Name;
  vector<Card*> Deck;
  vector<Card*> Sideboard;
  vector<Card*> Hand;
  vector<unique_ptr<CardInPlay>> CardsInPlay;
  vector<Card*> Graveyard, Exile;
};
