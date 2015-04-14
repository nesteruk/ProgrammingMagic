#include "stdafx.h"
#include "Mana.h"
#include <algorithm>

Mana::Mana()
  : Red(0)
  , Blue(0)
  , Green(0)
  , White(0)
  , Black(0)
  , Colorless(0)
  , HasXInCost(false)
{
}

void Mana::Read(std::string spec)
{
  transform(begin(spec), end(spec), begin(spec), ::toupper);
  std::string numeric;
  for (char c : spec)
  {
    if (isdigit(c))
    {
      numeric += c;
    } else
    {
      switch (c)
      {
      case 'R': ++Red; break;
      case 'G': ++Green; break;
      case 'B': ++Black; break;
      case 'W': ++White; break;
      case 'U': ++Blue; break;
      case 'X': HasXInCost = true; break;
      }
    }
  }

  if (!numeric.empty())
  {
    Colorless = atof(numeric.c_str());
  }
}

Mana::Mana(std::string spec)
  : Mana()
{
  Read(spec);
}

bool Mana::EnoughToPay(const Mana& cost)
{
  if (Red < cost.Red || Blue < cost.Blue || Green < cost.Green ||
    White < cost.White || Black < cost.Black) return false;

  return ConvertedManaCost <= cost.ConvertedManaCost;
}

int Mana::GetConvertedManaCost() const
{
  return Red + Green + Blue + White + Black + Colorless;
}