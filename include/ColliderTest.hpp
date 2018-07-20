#pragma once

#include <nds.h>

#include "Collider.hpp"

class ColliderTest
{
public:

  static ColliderTest *noCollider;
  
public:
  ColliderTest(Collider *in, Collider *on)
  {
    this->in = in;
    this->on = on;
  }

  ColliderTest(const ColliderTest &collider)
  {
    *this = collider;
  }
  
  ~ColliderTest() = default;

  ColliderTest	&operator=(const ColliderTest &collider)
  {
    this->in = collider.in;
    this->on = collider.on;
    return (*this);
  }

  void		set(Collider *in, Collider *on)
  {
    this->in = in;
    this->on = on;
  }

public:
  
  Collider	*in;
  Collider	*on;
};
