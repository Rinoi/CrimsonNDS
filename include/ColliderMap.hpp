#pragma once

#include "IColliderMap.hpp"

class ColliderMap : public IColliderMap
{
  static ColliderTile	CTile;
  
public:

  ColliderMap(int width, int height,
	      const vec2 &mul, const std::vector<u16> &collider);
  virtual ~ColliderMap();

  bool		getCollider(int x, int y) const;
  Collider	*get(int x, int y) const;
  void		setInMap(int x, int y, u16 b);
  void		addCollider(Collider *);
  void		removeCollider(Collider *);

  void		addInMap(u16 *map, int width, int height, int bMap = 0);
  u16		getInMap(int x, int y) const;
  
private:

  Collider	*checkList(int x, int y) const;
  ColliderTile	*setColiderTile(u16 idx, const vec2f &ptn) const;
  bool		isACollider(int x, int y) const;
  
private:

  std::vector<u16>	collider;
  std::list<Collider *>	colliderList;
  int			width;
  int			height;
  vec2			mul;
  u16			*map;
};
