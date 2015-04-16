#pragma once

#include <string>
#include <boost/preprocessor/seq.hpp>

#define MANACOLOR(_,__,N) int BOOST_PP_TUPLE_ELEM(3,0,N); \
  inline bool BOOST_PP_CAT(GetHas, BOOST_PP_TUPLE_ELEM(3,0,N))() const { \
    return BOOST_PP_TUPLE_ELEM(3,0,N) > 0; } \
  __declspec(property(get = BOOST_PP_CAT(GetHas, BOOST_PP_TUPLE_ELEM(3,0,N)))) \
  bool BOOST_PP_CAT(Has, BOOST_PP_TUPLE_ELEM(3,0,N));

#define PRIMARYMANA ((White, 'W', "Plains")) \
  ((Blue, 'U', "Island")) \
  ((Black, 'B', "Swamp")) \
  ((Red, 'R', "Mountain")) \
  ((Green, 'G', "Forest"))

#define ALLMANA PRIMARYMANA((Colorless, 'C', ""))
#include <ostream>

class Mana
{
public:
  BOOST_PP_SEQ_FOR_EACH(MANACOLOR, , ALLMANA);

  int X;

  Mana();
  void Read(std::string spec);
  Mana(std::string spec);

  bool EnoughToPay(const Mana& cost);

  int GetConvertedManaCost() const;
  __declspec(property(get = GetConvertedManaCost)) int ConvertedManaCost;

  std::string ToString() const;
  friend std::ostream& operator<<(std::ostream& os, const Mana& mana);
};
