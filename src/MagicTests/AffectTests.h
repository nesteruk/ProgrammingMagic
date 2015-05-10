#pragma once
#include <Game.h>
#include <CardDatabase.h>
#include <CardInPlay.h>

TEST(PlusOneTest, AffectTests)
{
  Game game;
  
  Card card;
  card.Name = "1/1 creature";
  card.Power = 1;
  card.Toughness = 1;

  Card card2;
  card2.Name = "Creature that gives +1/+1 to all";
  card2.Power = 1;
  card2.Toughness = 1;
  card2.Affects.push_back(
	  [](GameContext& ctx)
  {
	  ctx.Card.Power++;
	  ctx.Card.Toughness++;
  });

  auto cip1 = std::make_unique<CardInPlay>(game, card);
  auto cip2 = std::make_unique<CardInPlay>(game, card2);

  game.player.CardsInPlay.push_back(move(cip1));

  EXPECT_EQ(1, game.player.CardsInPlay[0]->Power);
  EXPECT_EQ(1, game.player.CardsInPlay[0]->Toughness);

  game.player.CardsInPlay.push_back(move(cip2));

  EXPECT_EQ(2, game.player.CardsInPlay[0]->Power);
  EXPECT_EQ(2, game.player.CardsInPlay[0]->Toughness);
}