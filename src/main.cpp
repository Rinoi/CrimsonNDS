#include <nds.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <list>

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
TBackground *bgs;
TBackground *bgs2;
Sprite		*a;
BColliderMap	*CMap;
BMap		*bMap;
bool    miss = false;
bool    jump = false;
int	    dt = 0;
float		v = 2.;
int		  sx = 0;
int     sxx = 0;
int		  bgx = 0;
vec2f		g_v = {2, 0};

std::list<Sprite *> my_list;

//MAP

const u16	O = 9;
const u16	M = 2;

u16		mapA[] =
  {
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M,
  };

u16		mapB[] =
  {
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M,
  };

u16		mapC[] =
  {
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, O, O, O, O, O, O, O, O, O, O, O, O, O, O, M,
    M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M,
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
  bg2 = new TBackground(TBackground::MAIN, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 0);
//  bgs = new TBackground(TBackground::SUB, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 1);
//  bgs2 = new TBackground(TBackground::SUB, BgSize_T_512x256, &rogueLikeSheet, TileLayer1, 16, 16, 0);

  BMap	mapBG({16, 16}, {2, 1}, true);
  
  bMap = new BMap({16, 16}, {2, 1}, true);
  CMap = new BColliderMap(bMap, {16, 16}, {M});

  mapBG.init(1);
  bMap->init(0);
  bMap->setMap(0, mapC);
  bMap->setMap(1, mapC);
  bg->addInMapT16(mapC, 16, 16, 0);
  bg->addInMapT16(mapC, 16, 16, 1);
  bg2->addInMapT16(mapBG.getData(), 16, 16, 0);
  bg2->addInMapT16(mapBG.getData(), 16, 16, 1);

  a = new Sprite(Sprite::MAIN, SpriteSize_16x16, &rogueLikeSheet, 50, Sprite::ABSOLUTE);
  a->setPos(128, 180);
  a->addCollider({1, 1}, {14, 14}, CMap);
  
  return (true);
}

bool		enginePreUpdate()
{
  g_v = {v, 0};  

  for (auto it=my_list.begin(); it != my_list.end(); ++it) {
    if((*it)->getPos().y != 1)
      (*it)->setPos((*it)->getPos().x, (*it)->getPos().y - 1);
    else {
 //     delete *it;
      it = my_list.erase(it);
    }
  }
  return (true);
}
bool		engineUpdate()
{
  // static int	bmap = 0;
  // static bool	b = false;
  return (true);
}

void		keyUp()
{
    if (a->getPos().y > 1)
      a->setPos(a->getPos().x, a->getPos().y - v);
}

void    keyDown()
{
    if (a->getPos().y  < 174)
      a->setPos(a->getPos().x, a->getPos().y + v);
}

void    keyUA()
{
  Sprite *missil = new Sprite(Sprite::MAIN, SpriteSize_16x16, &rogueLikeSheet, 16, Sprite::ABSOLUTE);
  missil->setPos(a->getPos().x, a->getPos().y - 16);
  my_list.push_back(missil);
}

void    keyUB()
{
  int random = rand() % 240 + 6;
  Sprite *mechant = new Sprite(Sprite::MAIN, SpriteSize_16x16, &rogueLikeSheet, 40, Sprite::ABSOLUTE);
  mechant->setPos(random, 1);
}


void		keyRight()
{
    if (a->getPos().x > 240)
      a->setPos(16, a->getPos().y);
    else
      a->setPos(a->getPos().x + v, a->getPos().y);
}

void		keyLeft()
{
  if (a->getPos().x < 6)
    a->setPos(230, a->getPos().y);
  else
    a->setPos(a->getPos().x - v, a->getPos().y);
}

int		main()
{
  Engine	engine;

  engine.start();
  return (0);
}
