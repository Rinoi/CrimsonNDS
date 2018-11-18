#pragma once

#include <nds.h>
#include <list>

#include "SpriteSheet.hpp"
#include "vec.hpp"

class Collider;
class IColliderMap;

class Sprite
{

public:

  enum Type
    {
      MAIN, SUB
    };

  enum Reference
    {
      ABSOLUTE, RELATIVE
    };

    static bool				updateSprites();

private:


  static bool				initSprites();

  static bool b;
  static bool mainId[128];
  static bool subId[128];

  static std::list<Sprite *>	spriteList;
  static std::list<Sprite *>	newSpriteList;


public:

  Sprite(Type type, SpriteSize size, SpriteSheet *spriteSheet, u16 idx,
	     Reference ref = Reference::ABSOLUTE);

  virtual ~Sprite();

  void		setPos(const vec2f &pos);
  void		setPos(float x, float y);
  void		scroll(int dx, int dy);
  void		setV(const vec2f &v);
  void		setV(float x, float y);
  void		setIdx(u16 idx);
  void		destroy();

  void		addCollider(const vec2f &add, const vec2f &size,
			    IColliderMap *colliderMap, u16 objId = 1);


public:

    const vec2f	&getPos() const
	{return this->pos;}

    Collider	*getCollider() const
	{return this->collider;}

    const char* getType() const {
	if (this->type == MAIN)
	    return "MAIN";
	else
	    return "SUB";
    }

protected:

  bool		init();
  void		initGfx();
  bool		update();
  void		setSize();
  u16		getNewId();

protected:

  virtual void		move();

protected:

  Type		type;
  SpriteSize	spriteSize;
  SpriteSheet	*spriteSheet;
  u16		idx;
  Reference	ref;

  vec2		size;
  bool		bUpdate;

  u16		id;
  vec2f		pos;
  vec2f		pScroll;
  vec2f		v;
  u16		lifeSpan;

  u16		*gfx;

  Collider	*collider;
};
