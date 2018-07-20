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

SpriteSheet	rogueLikeSheet((unsigned int *)rogueLikeTiles, rogueLikeTilesLen,
			       pal, palLen,
			       96, 160);
//global for game
TBackground	*bg;
TBackground	*bg2;
Sprite		*a;
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
    O, O, O, O, O, O, O, O, O, O, O, O, M, M, O, O,
    O, O, O, O, O, O, O, O, O, O, O, M, O, O, M, O,
    O, O, O, O, O, O, O, O, O, O, M, O, O, O, O, M,
    M, M, M, M, M, M, M, M, M, M, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
    O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O,
  };

bool		engineInit()
{
  bg = new TBackground(TBackground::SUB, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 1);
  bg2 = new TBackground(TBackground::SUB, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 0);

  BMap	mapBG({16, 16}, {2, 1}, true);
  
  bMap = new BMap({16, 16}, {2, 1}, true);
  CMap = new BColliderMap(bMap, {16, 16}, {M});

  mapBG.init(9);
  bMap->init(O);
  bMap->setMap(0, mapA);
  bMap->setMap(1, mapA);
  bg->addInMapT16(mapA, 16, 16, 0);
  bg->addInMapT16(mapA, 16, 16, 1);
  bg2->addInMapT16(mapBG.getData(), 16, 16, 0);
  bg2->addInMapT16(mapBG.getData(), 16, 16, 1);
  bg->addInMapT16(bMap->getMap(1).data, 16, 16, 1);

  a = new Sprite(Sprite::SUB, SpriteSize_16x16, &rogueLikeSheet, 42, Sprite::ABSOLUTE);
  a->setPos(0, 0);
  a->addCollider({1, 1}, {14, 14}, CMap);
  
  return (true);
}

bool		enginePreUpdate()
{
  g_v = {v, 0};

  if (a->getPos().x - sx < 256/2)
    g_v.x += v / 3.;
  
  if (jump == true)
    {
      dt += 1;

      if (dt == 50)
	{
	  dt = 0;
	  jump = false;
	}
      else if (a->getCollider()->willCollide({0, -v}) == false)
	g_v.y -= v;
    }
  else if (a->getCollider()->willCollide({0, v}) == false)
    g_v.y += v;
  a->setV(g_v.x, g_v.y);  
  return (true);
}

bool		engineUpdate()
{
  bg2->scroll(bgx, 0);
  bg->scroll(sx, 0);
  a->scroll(-sx, 0);
  sx += v;
  bgx += v / 2 > 0 ? v / 2 : 1;
  if (sx >= 512)
    {
      a->setPos(a->getPos().x - 512, a->getPos().y);
      sx = 0;
    }
  return (true);
}


void		keyDA()
{
  jump = true;  
}

void		keyUA()
{
  jump = false;
  dt = 0;
}

int		main()
{
  Engine	engine;

  engine.start();
  return (0);
}
