#pragma once

#include "Card.h"

TEST(CardZeroTest, CardTests)
{
  Card card;
  EXPECT_EQ(0,card.Cost.ConvertedManaCost);
  EXPECT_EQ(0,card.Power);
  EXPECT_EQ(0,card.Toughness);
  EXPECT_FALSE(card.CanAttack);
  EXPECT_EQ(Card::Rarity::Common, card.Rarity);
  EXPECT_TRUE(card.Name.empty());
  EXPECT_TRUE(card.Types.empty());
}

TEST(CardHasTypeTest, CardTests)
{
  Card card;
  card.Types = "Artifact Creature - Golem";
  EXPECT_TRUE(card.HasType("Artifact"));
  EXPECT_TRUE(card.HasType("Golem"));
  EXPECT_FALSE(card.HasType("Goblin"));
}

TEST(CardInitTest, CardTests)
{
  Card card;
  card.Name = "Fugitive Wizard";
  card.Types = "Creature - Human Wizard";
  card.Power = 1;
  card.Toughness = 1;

  EXPECT_TRUE(card.CanAttack);
  EXPECT_TRUE(card.IsCreature);
  EXPECT_TRUE(card.HasType("Wizard"));

  EXPECT_FALSE(card.IsLand);
  EXPECT_FALSE(card.HasType("Zombie"));
}

TEST(CardToStringTest, CardTests)
{
  Card card;
  card.HasFlying = true;
  card.HasFirstStrike = true;
  auto s = card.ToString();
  EXPECT_TRUE(s.find("Flying") != std::string::npos);
  EXPECT_TRUE(s.find("First Strike") != std::string::npos);
  EXPECT_TRUE(s.find("Vigilance") == std::string::npos);
}