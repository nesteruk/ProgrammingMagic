#include "stdafx.h"
#include "Mana.h"

Mana::Mana()
{
}

Mana::Mana(int n) : Mana()
{
  Colorless = n;
}

void Mana::Read(string spec)
{
#define MANACASE(_,__,N) case BOOST_PP_TUPLE_ELEM(3,1,N): ++BOOST_PP_TUPLE_ELEM(3,0,N); break;
  transform(begin(spec), end(spec), begin(spec), toupper);
  string numeric;
  for (char c : spec)
  {
    if (isdigit(c))
    {
      numeric += c;
    } else
    {
      switch (c)
      {
        BOOST_PP_SEQ_FOR_EACH(MANACASE,,PRIMARYMANA)
      case 'X': ++X; break;

      case '{': case '}': break; // take care of this later
      }
    }
  }

  if (!numeric.empty())
  {
    Colorless = atof(numeric.c_str());
  }
}

Mana::Mana(string spec)
  : Mana()
{
  Read(spec);
}

Mana Mana::Parse(string spec)
{
  Mana mana;
  mana.Read(spec);
  return mana;
}

bool Mana::EnoughToPay(const Mana& cost)
{
#define CHECKCOST(_,__,N) (BOOST_PP_TUPLE_ELEM(3,0,N) < cost.BOOST_PP_TUPLE_ELEM(3,0,N)) ||
  if (BOOST_PP_SEQ_FOR_EACH(CHECKCOST,,PRIMARYMANA) false) return false;

  return ConvertedManaCost >= cost.ConvertedManaCost;
}

int Mana::GetConvertedManaCost() const
{
  // todo: CMC on the stack includes the X that was substituted :|
#define SUMMANA(_,x,y) x + BOOST_PP_TUPLE_ELEM(3,0,y)
  return BOOST_PP_SEQ_FOLD_LEFT(SUMMANA,,ALLMANA);
}

string Mana::ToString() const
{
#define PRINTMANA(_,__,N) \
  for (size_t i = 0; i < BOOST_PP_TUPLE_ELEM(3,0,N); ++i) \
    s << BOOST_PP_TUPLE_ELEM(3,1,N);

  ostringstream s{};

  for (size_t i = 0; i < X; i++) s << 'X';
  if (HasColorless) s << Colorless;
  BOOST_PP_SEQ_FOR_EACH(PRINTMANA, , PRIMARYMANA)

  return s.str();
}

bool Mana::GetIsColoress() const
{
  // seems legit
  return ConvertedManaCost == Colorless;
}

ostream& operator<<(ostream& os, const Mana& mana)
{
  os << mana.ToString();
  return os;
}