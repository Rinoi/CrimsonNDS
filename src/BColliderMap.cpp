#include "BColliderMap.hpp"
#include <stdio.h>

#include "Collider.hpp"
#include "ColliderTile.hpp"
#include "HasCollider.hpp"
#include "vec.hpp"

#include <cstdio>

ColliderTile    BColliderMap::CTile(NULL, {0, 0}, 0);

BColliderMap::BColliderMap(BMap *bMap, const vec2 &mul, const std::vector<u16> &collider)
{
  this->mul = mul;
  this->bMap = bMap;
  this->collider = collider;
}

bool		BColliderMap::isACollider(int x, int y) const
{
  for (std::vector<u16>::const_iterator it = this->collider.begin();
       it != this->collider.end(); it++)
    if (this->getInMap(x, y) == *it)
      return (true);
  return (false);
}

bool		BColliderMap::getCollider(int x_g, int y_g) const
{
  int		x = x_g;
  int		y = y_g;

  x /= this->mul.x;
  y /= this->mul.y;

  if (x < 0)
    return (true);
  if (y < 0)
    return (true);
  if (x >= 256)
    return (true);
  if (y >= 256)
    return (true);

  return (this->isACollider(x, y));
}

Collider        *BColliderMap::get(int x_g, int y_g) const
{
  int		x = x_g;
  int		y = y_g;
  Collider	*tmp;

  // printf("map2 %p %p %d\n", this, this->bMap, this->mul.x);
  x /= this->mul.x;
  y /= this->mul.y;

  if (x < 0)
    return (this->setColiderTile((u16)(-1), {(float)(x), (float)(y)}));
  else if (y < 0)
    return (this->setColiderTile((u16)(-1), {(float)(x), (float)(y)}));
  else if (x >= 256)
    return (this->setColiderTile((u16)(-1), {(float)(x), (float)(y)}));
  else if (y >= 256)
    return (this->setColiderTile((u16)(-1), {(float)(x), (float)(y)}));

   if ((tmp = this->checkList(x_g, y_g)) != NULL)
     return (tmp);

  if (this->isACollider(x, y))
    return (this->setColiderTile(this->getInMap(x, y),
				 {(float)(x), (float)(y)}));
  return (NULL);
}

u16		BColliderMap::getInMap(int x, int y) const
{
  int		idx;

  // idx = y * this->width + x;
  if (x >= 256 || y >= 256 ||
      x < 0 || y < 0)
    return ((u16)(-1));

  // idx = y * this->mul.x + (x % (int)(this->mul.x));
  // if (x >= this->mul.x)
  //   idx += this->mul.x * 256;
  // printf("%d\n", (int)(this->map[idx]));
  return (this->bMap->get(x, y));
}

Collider	*BColliderMap::checkList(int x, int y) const
{
  std::list<Collider *>::const_iterator it = this->colliderList.begin();
  while (it != this->colliderList.end())
    {
      vec2f	ptn = (*it)->getPos();
      vec2f	size = (*it)->getSize();
      int	tmp;

      if (((*it) != Collider::currentTest) &&
	  ((tmp = x - ptn.x) > 0 && tmp < size.x) &&
	  ((tmp = y - ptn.y) > 0 && tmp < size.y))
	return ((*it));

      it++;
    }

  return (NULL);
}

void		BColliderMap::addCollider(Collider *c)
{
  this->colliderList.push_back(c);
}

void		BColliderMap::removeCollider(Collider *c)
{
  this->colliderList.remove(c);
}

ColliderTile	*BColliderMap::setColiderTile(u16 idx, const vec2f &ptn) const
{
  this->CTile.setIdx(idx);
  this->CTile.setPos(ptn);
  return (&this->CTile);
}
