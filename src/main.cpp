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
#include "spaceinvaders.h"

#include "pal.h"
#include "img.h"

#include "Mode.hpp"


bool init_step(int);

SpriteSheet	spaceinvadersSheet((unsigned int *)spaceinvadersTiles, spaceinvadersTilesLen,
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
int current_step = 1;

std::list<Sprite *> list_missil;
std::list<Sprite *> list_vilain;
std::list<Sprite *> list_blocks;

//MAP

const u16	O = 1;
const u16	M = 1;

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
  bg = new TBackground(TBackground::MAIN, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 1);
  bg2 = new TBackground(TBackground::MAIN, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 0);
  bgs = new TBackground(TBackground::SUB, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 1);
  bgs2 = new TBackground(TBackground::SUB, BgSize_T_512x256, &spaceinvadersSheet, TileLayer1, 16, 16, 0);

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

  bgs->addInMapT16(mapC, 16, 16, 0);
  bgs->addInMapT16(mapC, 16, 16, 1);
  bgs2->addInMapT16(mapBG.getData(), 16, 16, 0);
  bgs2->addInMapT16(mapBG.getData(), 16, 16, 1);

  a = new Sprite(Sprite::SUB, SpriteSize_16x16, &spaceinvadersSheet, 4, Sprite::ABSOLUTE);
  a->setPos(128, 180);
  a->addCollider({1, 1}, {14, 14}, CMap);

  init_step(current_step++);
  
  return (true);
}


bool init_step(int step)
{
   int x = 0;
   int xx = 0;
   int y = 0;
   int imax = 0;
   int jmax = 0;
   int decx = 0;
   int decy = 0;
   int enemy = 0;
  for (auto it=list_vilain.begin(); it != list_vilain.end(); ++it) {
      (*it)->destroy();
      it = list_vilain.erase(it);
  }   
  if (step == 1) {
       jmax = 1;
       imax = 5;
       decx = 40;
       decy = 17;
       xx = 40;
       y = 34;
       enemy = 2;
   } else if (step == 2) {
       jmax = 2;
       imax = 7;
       decx = 35;
       decy = 17;
       xx = 35;
       y = 17;
       enemy = 3;
   } else if (step == 3) {
       jmax = 3;
       imax = 10;
       decx = 20;
       decy = 17;
       xx = 30;
       y = 1;
       enemy = 5;
   }
   
   for (int j = 0; j < jmax; j++) {
	x = xx;
	for (int i = 0; i < imax; i++) {
	    Sprite *vilain = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, enemy, Sprite::ABSOLUTE);
	    vilain->setPos(x, y);
	    list_vilain.push_back(vilain);
	    x += decx;
	}
	y += decy;
    }


   y = 50;
    x = 50;
    for (int i = 0; i < 4; i++) {
	Sprite *block = new Sprite(Sprite::SUB, SpriteSize_16x16, &spaceinvadersSheet, 12, Sprite::ABSOLUTE);
	block->setPos(x, y);
	list_blocks.push_back(block);
	x += 50;
    }
    return (true);
}


bool		enginePreUpdate()
{
  g_v = {v, 0};  

  for (auto it=list_missil.begin(); it != list_missil.end(); ++it) {
      if((*it)->getPos().y > 0)
	  (*it)->setPos((*it)->getPos().x, (*it)->getPos().y - 2);
      else {
	  if ((*it)->getType() == "SUB") {
	      Sprite *missil = new Sprite(Sprite::MAIN, SpriteSize_16x16, &spaceinvadersSheet, 10, Sprite::ABSOLUTE);
	      missil->setPos((*it)->getPos().x, (*it)->getPos().y + 190);
	      (*it)->destroy();
	      (*it) = missil;	      
	  } else {
	      (*it)->destroy();
	      it = list_missil.erase(it);
	  }
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
/*
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
*/
void    keyUA()
{
  Sprite *missil = new Sprite(Sprite::SUB, SpriteSize_16x16, &spaceinvadersSheet, 10, Sprite::ABSOLUTE);
  missil->setPos(a->getPos().x, a->getPos().y - 16);
  list_missil.push_back(missil);
}

void    keyUB()
{
    init_step(current_step++);
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
