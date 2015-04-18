#include "stdafx.h"
#include "Card.h"

#include <boost/algorithm/string.hpp>
#include <sstream>

Card::~Card()
{
}

Card::Card()
  : power_(0)
  , toughness_(0)
  , Rarity(Rarity::Common)
{
#define SETFALSE(_,__,N) BOOST_PP_CAT(Has, BOOST_PP_SEQ_FOLD_LEFT(MERGE,,N)) = false;
  BOOST_PP_SEQ_FOR_EACH(SETFALSE,,CARDTRAITS)
}

std::string Card::GetTypes() const
{
  return types_;
}

void Card::SetTypes(std::string types)
{
  types_ = types;
}

int Card::GetPower() const
{
  return power_;
}

void Card::SetPower(int power)
{
  power_ = power;
}

std::string Card::ToString() const
{
  std::ostringstream s{};
  
  s << Name << " - ";
  s << Types << " ";
  if (IsCreature)
  {
    s << Power << "/" << Toughness << " ";
  }

  #define NORMAL(_,x,y) x y
  #define CHECKTRAIT(_,__,N) if (BOOST_PP_CAT(Has, BOOST_PP_SEQ_FOLD_LEFT(MERGE,,N))) \
      { s << BOOST_PP_STRINGIZE(BOOST_PP_SEQ_FOLD_LEFT(NORMAL,,N)) << " "; }

  BOOST_PP_SEQ_FOR_EACH(CHECKTRAIT,,CARDTRAITS)

  return s.str();
}

bool Card::HasType(const std::string& type) const
{
  return boost::to_upper_copy(Types)
    .find(boost::to_upper_copy(type)) != std::string::npos;
}

bool Card::GetCanAttack() const
{
  return Power > 0 && !HasCannotAttack;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
  os << card.ToString();
  return os;
}