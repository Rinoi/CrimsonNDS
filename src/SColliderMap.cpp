#include "SColliderMap.hpp"
#include <stdio.h>

#include "Collider.hpp"
#include "ColliderTile.hpp"
#include "HasCollider.hpp"
#include "vec.hpp"

ColliderTile    SColliderMap::CTile(NULL, {0, 0}, 0);

SColliderMap::SColliderMap(const vec2 &mul, u16 *map, const std::vector<u16> &collider)
{
  this->mul = mul;
  this->map = map;
  this->collider = collider;
}

bool		SColliderMap::isACollider(int x, int y) const
{
  for (std::vector<u16>::const_iterator it = this->collider.begin();
       it != this->collider.end(); it++)
    if (this->getInMap(x, y) == *it)
      return (true);
  return (false);
}

bool		SColliderMap::getCollider(int x_g, int y_g) const
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

Collider        *SColliderMap::get(int x_g, int y_g) const
{
  int		x = x_g;
  int		y = y_g;
  Collider	*tmp;

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

  if (this->isACollider(x, y))
    return (this->setColiderTile(this->getInMap(x, y),
				 {(float)(x), (float)(y)}));
  return (NULL);
}

u16		SColliderMap::getInMap(int x, int y) const
{
  int		idx;

  // idx = y * this->width + x;
  if (x >= 256 || y >= 256 ||
      x < 0 || y < 0)
    return ((u16)(-1));
  idx = y * this->mul.x + (x % (int)(this->mul.x));
  if (x >= this->mul.x)
    idx += this->mul.x * 256;
  // printf("%d\n", (int)(this->map[idx]));
  return (this->map[idx]);
}

ColliderTile	*SColliderMap::setColiderTile(u16 idx, const vec2f &ptn) const
{
  this->CTile.setIdx(idx);
  this->CTile.setPos(ptn);
  return (&this->CTile);
}
