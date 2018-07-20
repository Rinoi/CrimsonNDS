#pragma once

#include <nds.h>

#include "vec.hpp"
#include <list>
#include <vector>


class Collider;
class ColliderTile;

class IColliderMap
{
public:
  virtual ~IColliderMap() = default;
  
  virtual bool		getCollider(int x, int y) const = 0;
  virtual Collider	*get(int x, int y) const = 0;
};
