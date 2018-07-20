#pragma once

#include "IColliderMap.hpp"
#include "BMap.hpp"

//BLOCK COLLIDER MAP
class BColliderMap : public IColliderMap
{
  static ColliderTile   CTile;

public:
  
  BColliderMap(BMap *bMap, const vec2 &mul, const std::vector<u16> &collider);
  virtual ~BColliderMap() = default;

  bool			getCollider(int x, int y) const;
  Collider		*get(int x, int y) const;

  u16			getInMap(int x, int y) const;

private:

  ColliderTile		*setColiderTile(u16 idx, const vec2f &ptn) const;
  bool			isACollider(int x, int y) const;

private:
  BMap			*bMap;
  vec2			mul;
  std::vector<u16>	collider;
};
