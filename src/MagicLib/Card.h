#pragma once
#include "Mana.h"
#include <ostream>
#include <boost/preprocessor/stringize.hpp>
#include <utility>
#include <cinttypes>
#include "ActivatedAbility.h"
#include <vector>

#define CARDTRAITS ((Flying))((First)(Strike))((Haste)) \
  ((Vigilance))((Fear))((Unblockable))((Cannot)(Attack)) \
  ((Trample))((Intimidate))
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


class GameContext;
class CardInPlay;

class Card
{
  string type_line_;
  int power_ = 0, toughness_ = 0;
public:
  Card();
  virtual ~Card();

  enum class Rarity
  {
    Common,
    Uncommon,
    Rare,
    MythicRare
  } Rarity = Rarity::Common;

  enum class ExpansionSet
  {
    M15
  } ExpansionSet;

  uint16_t CardNumber;

  BOOST_PP_SEQ_FOR_EACH(TRAITFIELD, bool, CARDTRAITS);
  BOOST_PP_SEQ_FOR_EACH(TYPETEST,,TYPES);

  string Name;

  virtual string GetTypeLine() const;

  virtual void SetTypeLine(string type_line);

  __declspec(property(get = GetTypeLine, put = SetTypeLine)) string Types;
  
  virtual int GetPower() const;
  virtual void SetPower(int power);
  __declspec(property(get = GetPower, put = SetPower)) int Power;

  virtual int GetToughness() const { return toughness_; }
  virtual void SetToughness(int toughess) { toughness_ = toughess; }
  __declspec(property(get = GetToughness, put = SetToughness)) int Toughness;
  
  Mana ManaCost;
  // planeswalker only
  int Loyalty = 0;

  string ToString() const;
  friend ostream& operator<<(ostream& os, const Card& card);

  bool HasType(const string& type) const;

  virtual bool GetCanAttack() const;
  __declspec(property(get = GetCanAttack)) bool CanAttack;

  bool GetIsValid();
  __declspec(property(get = GetIsValid)) bool IsValid;

  // come to think of it, the way this card affects other cards
  // might be predicated by other cards :)
  // and we need to go deeper (C) inception
  vector<function<void(GameContext&)>> Affects;

  vector<ActivatedAbility> ActivatedAbilities;
};

#undef FIELDOFTYPE
#undef TYPETEST
#undef TRAITFIELD