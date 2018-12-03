#include <nds.h>
#include <stdio.h>

#include "MAP.h"
#include "map.h"

#include "hmap.h"
#include "Engine.hpp"
#include "mariolike.h"
#include "ColliderMap.hpp"
#include "Collider.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "TBackground.hpp"
#include "TBackground2.hpp"
#include "BColliderMap.hpp"
#include "BMap.hpp"
#include "pixel_tiles.h"

#include "pal.h"
#include "img.h"

#include "Mode.hpp"

SpriteSheet	mariolikeSheet((unsigned int *)mariolikeTiles, mariolikeTilesLen,
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
int scrolly = 4*16;



//MAP

const u16	O = 43;
const u16	M = 24;
int curmap = 1;

constexpr static int	nbMap = 6;

u16		*maps[nbMap] =
  {
    &Layer10[0],
    &Layer11[0],
    &Layer12[0],
    &Layer13[0],
    &Layer14[0],
    &Layer15[0],
  };

bool		engineInit()
{
//  bg = new TBackground2(TBackground2::MAIN, BgSize_T_512x256,  &mariolikeSheet, Layer10, 16, 16, 1, maps);
  bg = new TBackground(TBackground::MAIN, BgSize_T_512x256,  &mariolikeSheet, Layer10, 16, 16, 1);
  bg2 = new TBackground(TBackground::MAIN, BgSize_T_512x256, &mariolikeSheet, Layer10, 16, 16, 0);

  BMap	mapBG({16, 16}, {2, 1}, true);
  
  bMap = new BMap({16, 16}, {2, 1}, true);
  CMap = new BColliderMap(bMap, {16, 16}, {3,4,5,7,8,9,10,11,12,13,14,15,16,17,21,22,23,28,29});

  mapBG.init(0);
  bMap->init(0);
  bMap->setMap(0, Layer10);
  bMap->setMap(1, Layer10);
  bg->addInMapT16(Layer10, 16, 16, 0);
  bg->addInMapT16(Layer10, 16, 16, 1);
  bg2->addInMapT16(mapBG.getData(), 16, 16, 0);
  bg2->addInMapT16(mapBG.getData(), 16, 16, 1);
  bg->addInMapT16(bMap->getMap(1).data, 16, 16, 1);
  bg->scroll(0, scrolly);

  a = new Sprite(Sprite::MAIN, SpriteSize_16x16, &mariolikeSheet, 36, Sprite::ABSOLUTE);
  a->setPos(0,0);
  //a->setPos(50, 130);
  a->addCollider({1, 1}, {14, 14}, CMap, 2);

  return (true);
}

bool		enginePreUpdate()
{
	g_v = {v, 0};

	if (a->getPos().x - sx < 256/2)
		g_v.x += v / 3.;

	if (jump == true) {
		dt += 1;
		if (dt == 50) {
			dt = 0;
			jump = false;
		}
		else if (a->getCollider()->willCollide({0, -v}) == false)
			g_v.y -= v;
	}
	else if (a->getCollider()->willCollide({0, v + 0.75f}) == false)
		g_v.y += v + 0.75f;
    a->setV(0, g_v.y);
	return (true);
}

void		changeMap(int &bmap)
{
	if (curmap == 6)
		curmap = 0;
 u16	*map = maps[curmap++];

 bMap->setMap(bmap, map);
 bg->addInMapT16(map, 16, 16, bmap);
 //CMap = new BColliderMap(bMap, {16, 16}, {3,4,5,7,8,9,10,11,12,13,14,15,16,17,21,22,23,28,29});
 //a->addCollider({1, 1}, {14, 14}, CMap);

 bmap = (bmap + 1) % 2;
 // printf("change %p\n", map);
}

bool		engineUpdate()
{
  static int	bmap = 0;
  static bool	b = false;
  
  //bg2->scroll(bgx, scrolly);
//  bg->scroll(sx, scrolly);
//  a->scroll(-sx, 0);
  sx += v;
  bgx += v / 2 > 0 ? v / 2 : 1;
  // printf("%d\n", sx);
  if (b == false && sx >= 256)
    {
	//bg->changeMap(bmap, curmap);
      b = true;
    }
  if (sx >= 512)
    {
      //a->setPos(a->getPos().x - 512, a->getPos().y);
      sx = 0;
      //bg->changeMap(bmap, curmap);
      b = false;
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

void		keyRight()
{
    if (a->getPos().x == 200) {
        sx += v;
        //bgx += v / 2 > 0 ? v / 2 : 1;
        bg->scroll(sx, scrolly);
    }   else
	    a->setPos(a->getPos().x + v, a->getPos().y);

}

void		keyLeft()
{
	if (a->getPos().x == 20) {
	        sx -= v;
            //bgx -= v / 2 > 0 ? v / 2 : 1;
            bg->scroll(-sx, scrolly);
    } else
	    a->setPos(a->getPos().x - v, a->getPos().y);
}

int		main()
{
  Engine	engine;

  engine.start();
  return (0);
}
