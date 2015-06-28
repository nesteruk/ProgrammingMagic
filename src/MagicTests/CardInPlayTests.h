#pragma once

TEST(UniqueIdTest, CardInPlayTests)
{
	std::cout << "In uniqueness test" << std::endl;

	Game game;
	Card card;
	CardInPlay cip(game, card);

	EXPECT_EQ(0, cip.Uid) << "expected Uid to be 0, got " << cip.Uid;

	CardInPlay another(game, card);

	EXPECT_EQ(1, another.Uid);
}