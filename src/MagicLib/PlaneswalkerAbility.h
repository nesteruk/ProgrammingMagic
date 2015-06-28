#pragma once

class Game;

class PlaneswalkerAbility
{
public:
  int Cost;

  function<void(Game)> Action;
};
