#pragma once
#include "Mana.h"
#include <functional>

class Game;

class ActivatedAbility
{
public:
	// how much mana you have to pay
	Mana ManaCost;
	// whether you need to tap the card
	bool RequiresTap;
	// todo: additional payment details

	// what it actually does
	std::function<void(Game)> Action;
};
