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

  auto cip1 = std::make_unique<CardInPlay>(game, card);
  auto cip2 = std::make_unique<CardInPlay>(game, card);
  cip2->Affects.push_back(
    [](GameContext& ctx)
    {
      ctx.Card.Power++;
      ctx.Card.Toughness++;
    });

  game.player.CardsInPlay.push_back(move(cip1));
  

  EXPECT_EQ(1, game.player.CardsInPlay[0]->Power);
  EXPECT_EQ(1, game.player.CardsInPlay[0]->Toughness);

  game.player.CardsInPlay.push_back(move(cip2));

  EXPECT_EQ(2, game.player.CardsInPlay[0]->Power);
  EXPECT_EQ(2, game.player.CardsInPlay[0]->Toughness);
}