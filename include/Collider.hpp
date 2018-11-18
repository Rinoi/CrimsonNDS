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
	   IColliderMap *colliderMap, void *obj, u16 objId = 0);

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

  int       getObjId() const
  {
    return (this->objId);
  }

protected:

  vec2f			&ptn;
  vec2f			add;
  vec2f			size;
  IColliderMap		*map;
  u16			objId;
  void			*obj;
  bool b;
};
