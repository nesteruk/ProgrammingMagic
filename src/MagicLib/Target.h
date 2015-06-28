#pragma once

// anything that can be targeted
class Target
{
protected:
  ~Target()
  {
  }

public:
  virtual void Foo() {};
};
