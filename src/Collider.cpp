#include "Collider.hpp"

#include "ColliderMap.hpp"
#include "ColliderTest.hpp"

#include <cstdio>

Collider	*Collider::currentTest = NULL;
ColliderTest	Collider::cTest(NULL, NULL);

Collider::Collider(vec2f &vec, const vec2f &add, const vec2f &size,
			   IColliderMap *colliderMap, u16 colliderIdx, void *obj) :
  ptn(vec)
{
  this->add = add;
  this->size = size;
  this->map = colliderMap;
  this->obj = obj;
}

Collider::~Collider()
{

}

ColliderTest		*Collider::setTest(Collider *in, Collider *on)
{
  this->cTest.set(in, on);
  return (&this->cTest);
}

ColliderTest		*Collider::getTest(const vec2f &vector)
{
  int           x = this->ptn.x + this->add.x + vector.x;
  int           y = this->ptn.y + this->add.y + vector.y;
  Collider	*on = NULL;
  
  Collider::currentTest = this;

  if (vector.x != 0)
    {
      if (vector.x > 0)
	{
	  // printf("map : %p\n", this->map);
	  if ((on = this->map->get(x + this->size.x - 1, y)) != NULL)
	    return (this->setTest(this, on));
	  if ((on = this->map->get(x + this->size.x - 1,
				   y + this->size.y - 1)) != NULL)
	    return (this->setTest(this, on));
	}
      else
	{
	  if ((on = this->map->get(x, y)) != NULL)
	    return (this->setTest(this, on));
	  if ((on = this->map->get(x,
				   y + this->size.y - 1)) != NULL)
	    return (this->setTest(this, on));
	}
    }
  if (vector.y != 0)
    {
      if (vector.y > 0)
	{
	  if ((on = this->map->get(x, y + this->size.y - 1)) != NULL)
	    return (this->setTest(this, on));
	  if ((on = this->map->get(x + this->size.x - 1,
				   y + this->size.y - 1)) != NULL)
	    return (this->setTest(this, on));
	}
      else
	{
	  if ((on = this->map->get(x, y)) != NULL)
	    return (this->setTest(this, on));
	  if ((on = this->map->get(x + this->size.x - 1,
				   y)) != NULL)
	    return (this->setTest(this, on));
	}
    }
  return (ColliderTest::noCollider);
}

bool			Collider::willCollide(const vec2f &v)
{
  return (this->getTest(v) != ColliderTest::noCollider);
}
