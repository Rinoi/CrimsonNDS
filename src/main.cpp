#include <nds.h>
#include <stdio.h>

#include "map.h"

#include "hmap.h"
#include "Engine.hpp"
#include "rogueLike.h"
#include "ColliderMap.hpp"
#include "Collider.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "TBackground.hpp"
#include "BColliderMap.hpp"
#include "BMap.hpp"
#include "pixel_tiles.h"

#include "pal.h"
#include "img.h"

#include "Mode.hpp"

#include "ColliderTest.hpp"

class Missil : public Sprite
{
public:
  Missil(Type type, SpriteSize size, SpriteSheet *spriteSheet, u16 idx, Reference ref = Reference::ABSOLUTE) :
    Sprite::Sprite(type, size, spriteSheet, idx, ref)
  {

  }

protected:
  void		move()
  {
    vec2f			v = this->v;

    if (this->collider != NULL)
      {
	if (this->collider->willCollide({0, 0}) == true)
	  this->destroy();
	ColliderTest *test;
	if ((test = this->collider->getTest(v)) != NULL)
	  {
	    if (test->on->getObjId() == 0)
	      {
		this->destroy();
	      }
	    else
	      {
		Sprite *sp = (Sprite *)test->on->getObj();

		sp->destroy();
		this->destroy();
	      }
	    // printf("o => %f %f\n", v.x, v.y);
	  }
	else
	  goto deplace;
      }
    else
      {
      deplace:
	this->pos.x += v.x;
	this->pos.y += v.y;
	this->bUpdate = true;
      }
  }

};

SpriteSheet	rogueLikeSheet((unsigned int *)rogueLikeTiles, rogueLikeTilesLen,
			       pal, palLen,
			       96, 160);
//global for game
TBackground	*bg;
TBackground	*bg2;
Sprite		*a;
Sprite		*b;
Sprite		*c;
BColliderMap	*CMap;
BMap		*bMap;
bool		jump = false;
int		dt = 0;
float		v = 2.;
int		sx = 0;
int		bgx = 0;
vec2f		g_v = {2, 0};


//MAP

const u16	O = 43;
const u16	M = 24;

u16		mapA[] =
  {
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    O, M, O, O, O, O, O, O, O, O, O, O, O, O, M, O,
    O, O, M, O, O, O, O, O, O, O, O, O, M, M, O, O,
    O, O, O, M, M, M, M, M, M, M, M, M, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
  };

u16		mapB[] =
  {
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, M, M, O, O, O, O, O, O, O, O, O, O, O,
    M, M, M, O, M, O, O, O, O, O, O, O, O, O, O, M,
    O, O, O, O, M, O, O, O, O, O, O, O, O, O, M, O,
    O, O, O, O, M, O, O, O, O, O, O, O, M, M, O, O,
    O, O, O, O, M, M, M, M, M, M, M, M, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
  };

u16		mapC[] =
  {
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
  };

constexpr static int	nbMap = 3;

u16		*maps[nbMap] =
  {
    &mapA[0],
    &mapB[0],
    &mapC[0],
  };

bool		engineInit()
{
  bg = new TBackground(TBackground::MAIN, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 1);
  // bg2 = new TBackground(TBackground::MAIN, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 0);

  BMap	mapBG({16, 16}, {2, 1}, true);

  bMap = new BMap({16, 16}, {2, 1}, true);
  CMap = new BColliderMap(bMap, {16, 16}, {M});

  mapBG.init(1);
  bMap->init(O);
  bMap->setMap(0, mapC);
  // bMap->setMap(1, mapC);
  bg->addInMapT16(mapC, 16, 16, 0);
  // bg->addInMapT16(mapC, 16, 16, 1);
  // bg2->addInMapT16(mapBG.getData(), 16, 16, 0);
  // bg2->addInMapT16(mapBG.getData(), 16, 16, 1);
  // bg->addInMapT16(bMap->getMap(1).data, 16, 16, 1);

  a = new Sprite(Sprite::MAIN, SpriteSize_16x16, &rogueLikeSheet, 42, Sprite::ABSOLUTE);
  a->setPos(128, 50);
  a->addCollider({1, 1}, {14, 14}, CMap);

  b = new Missil(Sprite::MAIN, SpriteSize_16x16, &rogueLikeSheet, 42, Sprite::ABSOLUTE);
  b->setPos(128, 0);
  b->addCollider({1, 1}, {14, 14}, CMap);
  b->setV(0, 0.5);

  c = new Missil(Sprite::MAIN, SpriteSize_16x16, &rogueLikeSheet, 42, Sprite::ABSOLUTE);
  c->setPos(150, 0);
  c->addCollider({1, 1}, {14, 14}, CMap);
  c->setV(0, 0.5);

  return (true);
}

int		main()
{
  Engine	engine;

  engine.start();
  return (0);
}
