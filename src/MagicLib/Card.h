#pragma once
#include "Mana.h"
#include <ostream>
#include <boost/preprocessor/stringize.hpp>
#include <utility>

#define CARDTRAITS ((Flying))((First)(Strike))((Haste)) \
  ((Vigilance))((Fear))((Unblockable))((Cannot)(Attack)) \
  ((Trample))
#define TYPES (Artifact)(Conspiracy)(Creature)(Enchantment)(Instant)\
  (Land)(Phenomenon)(Plane)(Planeswalker)(Scheme)(Sorcery)(Tribal)(Vanguard)
#define SUPERTYPES (Basic)(Legendary)(Ongoing)(Snow)(World)
#define SUBTYPES (Equipment)(Fortification)(Aura)
#define MERGE(_,x,y) BOOST_PP_CAT(x,y)
#define TRAITFIELD(_,t,N) \
  t BOOST_PP_CAT(Has, BOOST_PP_SEQ_FOLD_LEFT(MERGE,,N));
#define TYPETEST(_,__,N) \
  inline bool BOOST_PP_CAT(GetIs, N)() const { \
    return HasType(BOOST_PP_STRINGIZE(N)); } \
    __declspec(property(get=BOOST_PP_CAT(GetIs, N))) bool BOOST_PP_CAT(Is, N);

class Card
{
  std::string type_line_;
  int power_, toughness_;
public:
  Card();
  virtual ~Card();

  enum class Rarity
  {
    Common,
    Uncommon,
    Rare,
    MythicRare
  } Rarity;

  BOOST_PP_SEQ_FOR_EACH(TRAITFIELD, bool, CARDTRAITS);
  BOOST_PP_SEQ_FOR_EACH(TYPETEST,,TYPES);

  std::string Name;

  virtual std::string GetTypeLine() const;

  virtual void SetTypeLine(std::string type_line);

  __declspec(property(get = GetTypeLine, put = SetTypeLine)) std::string Types;
  
  virtual int GetPower() const;
  virtual void SetPower(int power);
  __declspec(property(get = GetPower, put = SetPower)) int Power;

  virtual int GetToughness() const { return toughness_; }
  virtual void SetToughness(int toughess) { toughness_ = toughess; }
  __declspec(property(get = GetToughness, put = SetToughness)) int Toughness;
  
  Mana ManaCost;

  std::string ToString() const;
  friend std::ostream& operator<<(std::ostream& os, const Card& card);

  bool HasType(const std::string& type) const;

  virtual bool GetCanAttack() const;
  __declspec(property(get = GetCanAttack)) bool CanAttack;
};

#undef FIELDOFTYPE
#undef TYPETEST
#undef TRAITFIELD