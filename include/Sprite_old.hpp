// #pragma once

// #include <nds.h>
// #include <list>
// #include "SpriteSheet.hpp"
// #include "ptn.h"

// #include "HasCollider.hpp"

// class Collider;
// class ColliderMap;

// class Sprite : public HasCollider
// {

// public:
  
//   enum Type
//     {
//       MAIN, SUB
//     };

// public:

//   static std::list<Sprite *>	spriteList;
//   static std::list<Sprite *>	newSpriteList;
//   static void			SpriteAction(int action, Sprite *s = NULL);
  
// public:

//   Sprite(Type type, SpriteSize size, SpriteSheet *spriteSheet, u16 idx);

//   virtual ~Sprite();

//   bool		update();
//   void		move();
  
//   void		addCollider(const t_ptn &add, const t_ptn &size, ColliderMap *);
//   void		setPtn(int x, int y);  
//   void		setV(float x, float y);
//   void		setIdx(u16 idx);
//   void		setLiveSpan(u16 live);
//   void		destroy()
//   {this->setLiveSpan(0);}
  
//   t_ptn		getPos() const;

//   void		setScroll(const t_ptn &scroll)
//   {this->scroll = scroll;}
  
//   void		setPtn(const t_ptn &ptn)
//   {this->setPtn(ptn.x, ptn.y);}

//   const t_ptn	&getPtn() const
//   {return (this->ptn);}

//   const t_ptn	&getV() const
//   {return (this->v);}

//   const u16	&getTypeID() const
//   {return (this->typeId);}
  
//   void		setTypeID(u16 typeId)
//   {this->typeId = typeId;}
  
//   void		setV(const t_ptn &ptn)
//   {this->setV(ptn.x, ptn.y);}

//   void		onCollider(void (*fCollider)(HasCollider *in, HasCollider *on))
//   {this->fCollider = fCollider;}


//   void		setPersonalId(u16 personalId)
//   {this->personalId = personalId;}

//   u16		getPersonalId() const
//   {return (this->personalId);}
  
// protected:
  
//   bool		init();
//   void		initGfx();
//   u16		liveAct();
  
//   u16		getNewId(int act = -1);
  
// protected:
  
//   Type		type;
//   u16		typeId;
//   SpriteSize	size;
//   u16		width;
//   u16		height;
//   t_ptn       	ptn;
//   t_ptn       	v;
//   t_ptn		scroll;
//   u16		*gfx;
//   SpriteSheet	*spriteSheet;
//   Collider	*collider;
//   u16		idx;
//   u16		id;
//   bool		bUpdate;
//   bool		bV;
//   u16		liveSpan;
//   u16		personalId;
// };
