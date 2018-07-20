#pragma once

#include <vector>
#include "IColliderMap.hpp"

//STATIC COLLIDER MAP
class SColliderMap : public IColliderMap
{
  static ColliderTile   CTile;

public:
  SColliderMap(const vec2 &mul, u16 *map, const std::vector<u16> &collider);
  virtual ~SColliderMap() = default;

  bool			getCollider(int x, int y) const;
  Collider		*get(int x, int y) const;
  
  u16			getInMap(int x, int y) const;
  
private:

  ColliderTile		*setColiderTile(u16 idx, const vec2f &ptn) const;
  bool			isACollider(int x, int y) const;

private:
  u16			*map;
  vec2			mul;
  std::vector<u16>	collider;
};
