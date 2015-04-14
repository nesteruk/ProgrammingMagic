#pragma once

#include <string>

class Mana
{
public:
  int Red, Blue, Green, White, Black;
  int Colorless;
  bool HasXInCost;

  Mana();
  void Read(std::string spec);
  Mana(std::string spec);

  bool EnoughToPay(const Mana& cost);

  int GetConvertedManaCost() const;
  __declspec(property(get = GetConvertedManaCost)) int ConvertedManaCost;
};
