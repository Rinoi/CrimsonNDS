#pragma once

#include <nds.h>

#include "Collider.hpp"

class ColliderTile : public Collider
{
public:
  ColliderTile(IColliderMap *colliderMap, const vec2f &pos, u16 idx) :
    Collider(this->pos, {0, 0}, {1, 1}, colliderMap, &this->idx, 0)
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

  const vec2f &getPos() const
  {
    return this->pos;
  }

  const u16		getIdx() const
  {
    return this->idx;
  }
private:
  vec2f		pos;
  u16		idx;
};
