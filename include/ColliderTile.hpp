#pragma once

#include <nds.h>

#include "Collider.hpp"

class ColliderTile : public Collider
{
public:
  ColliderTile(IColliderMap *colliderMap, const vec2f &pos, u16 idx) :
    Collider(this->pos, {0, 0}, {1, 1}, colliderMap, 0, &this->idx)
  {
    this->pos = pos;
    this->idx = idx;
    // this->pos = ;
    // this->obj = (void*)(idx);
    // this->colliderIdx = 0;
  }

  virtual ~ColliderTile() = default;


  void		setIdx(u16 idx)
  {
    this->idx = idx;
  }

  void		setPos(const vec2f &pos)
  {
    this->pos = pos;
  }
  
private:
  vec2f		pos;
  u16		idx;
};
