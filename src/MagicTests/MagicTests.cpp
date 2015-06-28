#include "stdafx.h"
#include <MagicLib.h>
#include "ManaTests.h"
#include "CardTests.h"
#include "PropertyTests.h"
#include "AffectTests.h"
#include "CardInPlayTests.h"

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

