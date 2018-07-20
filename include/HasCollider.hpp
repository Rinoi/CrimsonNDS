// #pragma once

// #include <nds.h>
// #include "ptn.h"

// class Sprite;
// class ColliderTile;

// class HasCollider
// {
// public:
//   HasCollider(u16 objType)
//   {
//     this->fCollider = NULL;
//     this->objType = objType;
//   }
  
//   virtual ~HasCollider()
//   {}

//   u16		getObjType() const
//   {return this->objType;}
  

//   Sprite	*getSprite();
//   ColliderTile	*getColliderTile();

// protected:

//   u16		objType;
//   void		(*fCollider)(HasCollider *in, HasCollider *on);
// };

// class ColliderTile : public HasCollider
// {
// public:
//   ColliderTile(u16 idx, const t_ptn &pos) : HasCollider(1)
//   {this->idx = idx; this->pos = pos;}
//   virtual ~ColliderTile(){}

//   void	setIdx(u16 idx){this->idx = idx;}
//   u16	getIdx() const {return (this->idx);}

//   void	setPos(const t_ptn &pos){this->pos = pos;}
//   t_ptn	getPos() const {return (this->pos);}
  
// private:
//   u16	idx;
//   t_ptn	pos;
// };
