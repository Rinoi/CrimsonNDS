#pragma once

#include <nds.h>

#include "vec.hpp"

class IColliderMap;
class ColliderTest;

class Collider
{
public:
  static Collider	*currentTest;
private:
  static ColliderTest	cTest;
  
public:
  Collider(vec2f &vec, const vec2f &add, const vec2f &size,
	   IColliderMap *colliderMap, u16 colliderIdx, void *obj);

  virtual ~Collider();
  
  ColliderTest		*getTest(const vec2f &v);
  bool			willCollide(const vec2f &v);

private:
  ColliderTest		*setTest(Collider *in, Collider *on);
  
public:

  vec2f			getPos() const
  {
    vec2f		ptn = this->ptn;

    ptn.x += add.x;
    ptn.y += add.y;

    return (ptn);
  }


  const vec2f		&getSize() const
  {
    return (this->size);
  }
  
  void			*getObj() const
  {
    return (this->obj);
  }

protected:
  
  vec2f			&ptn;
  vec2f			add;
  vec2f			size;
  IColliderMap		*map;
  u16			colliderIdx;
  void			*obj;
};
