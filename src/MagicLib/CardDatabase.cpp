#include "stdafx.h"
#include "CardDatabase.h"

CardDatabase::CardDatabase()
{
  Card accursed_spirit;
  accursed_spirit.Name = "Accursed Spirit";
  accursed_spirit.ManaCost.Read("3B");
  accursed_spirit.Types = "Creature — Spirit";
  accursed_spirit.Power = 3;
  accursed_spirit.Toughness = 2;
  accursed_spirit.Rarity = Card::Rarity::Common;
  accursed_spirit.ExpansionSet = Card::ExpansionSet::M15;
  accursed_spirit.CardNumber = 85;
  accursed_spirit.HasIntimidate = true;
  Cards.emplace_back(accursed_spirit);

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