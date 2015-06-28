#pragma once

#define MANAZEROTEST(_,x,N) ASSERT_EQ(0, x.BOOST_PP_TUPLE_ELEM(3,0,N));

TEST(ManaDefaultTest, ManaTests)
{
  Mana mana;
  BOOST_PP_SEQ_FOR_EACH(MANAZEROTEST, mana, ALLMANA);
}

TEST(ManaInitTest, ManaTests)
{
  Mana mana("3rrgb");
  EXPECT_EQ(3, mana.Colorless);
  EXPECT_EQ(2, mana.Red);
  EXPECT_EQ(1, mana.Green);
  EXPECT_EQ(1, mana.Black);
  EXPECT_EQ(0, mana.X);
  EXPECT_EQ(7, mana.ConvertedManaCost);
}

TEST(ManaZeroTest, ManaTests)
{
  Mana m1("");
  Mana m2{ "" };
  EXPECT_EQ(0, m1.ConvertedManaCost);
  EXPECT_EQ(0, m2.ConvertedManaCost);

  EXPECT_TRUE(m1.EnoughToPay(m2));
  EXPECT_TRUE(m2.EnoughToPay(m1));

  Mana m3 = "3gr";
  EXPECT_TRUE(m3.EnoughToPay(m1));
  EXPECT_FALSE(m2.EnoughToPay(m3));
}

TEST(ManaIntInitTest, ManaTests)
{
  Mana m = 5;
  EXPECT_EQ(5, m.Colorless);
  EXPECT_EQ(0, m.Red);
}

TEST(ManaPaymentTest, ManaTests)
{
  Mana cost("3gg");
  Mana pool("rgbgr");
  EXPECT_TRUE(pool.EnoughToPay(cost));

  Mana cost2("rggg");
  EXPECT_FALSE(pool.EnoughToPay(cost2));
}

TEST(ManaPreseceTest, ManaTests)
{
  Mana mana("4wb");
  EXPECT_TRUE(mana.HasWhite);
  EXPECT_TRUE(mana.HasBlack);
  EXPECT_FALSE(mana.HasBlue);
  EXPECT_FALSE(mana.HasGreen);
  EXPECT_FALSE(mana.HasRed);
}

TEST(ManaPrintTest, ManaTests)
{
  Mana none{};
  std::string s = none.ToString();
  EXPECT_TRUE(s.empty());

  Mana mana("wubrg");
  EXPECT_EQ("WUBRG", mana.ToString());

  Mana mana2("3xxr");
  EXPECT_EQ("XX3R", mana2.ToString());

  Mana mana3("rrggbbwwuu");
  EXPECT_EQ("WWUUBBRRGG", mana3.ToString());
}