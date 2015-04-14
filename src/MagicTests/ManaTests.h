#pragma once

#include "Mana.h"

TEST(ManaInitTest, ManaTests)
{
  Mana mana("3rgb");
  EXPECT_EQ(3, mana.Colorless);
  EXPECT_EQ(1, mana.Red);
  EXPECT_EQ(1, mana.Green);
  EXPECT_EQ(1, mana.Black);
  EXPECT_FALSE(mana.HasXInCost);
}

TEST(ManaPaymentTest, ManaTests)
{
  Mana cost("3gg");
  Mana pool("rgbgr");
  EXPECT_TRUE(pool.EnoughToPay(cost));
}