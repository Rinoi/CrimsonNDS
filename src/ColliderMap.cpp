#include "ColliderMap.hpp"
#include <stdio.h>

#include "Collider.hpp"
#include "ColliderTile.hpp"
#include "HasCollider.hpp"
#include "vec.hpp"

ColliderTile	ColliderMap::CTile(NULL, {0, 0}, 0);

ColliderMap::ColliderMap(int width, int height,
			 const vec2 &mul, const std::vector<u16> &collider)
{
  this->width = width;
  this->height = height;
  this->map = new u16[width * height];
  dmaFillWords(0, this->map, width * height * sizeof(u16));
  this->mul = mul;
  this->collider = collider;
}

ColliderMap::~ColliderMap()
{
  delete [] this->map;
}

bool		ColliderMap::isACollider(int x, int y) const
{
  for (std::vector<u16>::const_iterator it = this->collider.begin();
       it != this->collider.end(); it++)
    if (this->getInMap(x, y) == *it)
      return (true);
  return (false);
}

bool		ColliderMap::getCollider(int x_g, int y_g) const
{
  int		x = x_g;
  int		y = y_g;
  
  x /= this->mul.x;
  y /= this->mul.y;

  if (x < 0)
    return (true);
  if (y < 0)
    return (true);
  if (x >= this->width)
    return (true);
  if (y >= this->height)
    return (true);

  if (this->checkList(x_g, y_g) != NULL)
    return (true);


  return (this->isACollider(x, y));
}

Collider	*ColliderMap::checkList(int x, int y) const
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

void		ColliderMap::addCollider(Collider *c)
{
  this->colliderList.push_back(c);
}

void		ColliderMap::removeCollider(Collider *c)
{
  this->colliderList.remove(c);
}

ColliderTile   *ColliderMap::setColiderTile(u16 idx, const vec2f &ptn) const
{
  this->CTile.setIdx(idx);
  this->CTile.setPos(ptn);
  return (&this->CTile);
}

Collider	*ColliderMap::get(int x_g, int y_g) const
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
  else if (x >= this->width)
    return (this->setColiderTile((u16)(-1), {(float)(x), (float)(y)}));
  else if (y >= this->height)
    return (this->setColiderTile((u16)(-1), {(float)(x), (float)(y)}));

  if ((tmp = this->checkList(x_g, y_g)) != NULL)
    return (tmp);

  if (this->isACollider(x, y))
    return (this->setColiderTile(this->getInMap(x, y),
				 {(float)(x), (float)(y)}));
  return (NULL);
}

void		ColliderMap::setInMap(int x, int y, u16 b)
{
  int		idx;

  if (x >= this->width || y >= this->height ||
      x < 0 || y < 0)
    return ;
  idx = y * this->mul.x + (x % (int)(this->mul.x));
  if (x >= this->mul.x)
    idx += this->mul.x * this->height;
  this->map[idx] = b;
}


void		ColliderMap::addInMap(u16 *map, int width, int height, int bMap)
{
  int		size;

  size = width * height * 2;
  // this->map = map;
  dmaCopy(map, this->map + (bMap * (size / 2)), size);
}

u16		ColliderMap::getInMap(int x, int y) const
{
  int		idx;

  // idx = y * this->width + x;
  if (x >= this->width || y >= this->height ||
      x < 0 || y < 0)
    return ((u16)(-1));
  idx = y * this->mul.x + (x % (int)(this->mul.x));
  if (x >= this->mul.x)
    idx += this->mul.x * this->height;
  // printf("%d\n", (int)(this->map[idx]));
  return (this->map[idx]);
}
