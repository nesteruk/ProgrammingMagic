#include "stdafx.h"
#include "CardDatabase.h"

CardDatabase::CardDatabase()
{
  Card bronze_sable;
  bronze_sable.Name = "Bronze Sable";
  bronze_sable.ManaCost = 2;
  bronze_sable.Types = "Artifact Creature — Sable";
  bronze_sable.Power = 2;
  bronze_sable.Toughness = 1;
  bronze_sable.Rarity = Card::Rarity::Common;
  bronze_sable.ExpansionSet = Card::ExpansionSet::M15;
  bronze_sable.CardNumber = 214;
  Cards.emplace_back(bronze_sable);
}