#include <nds.h>
#include <stdio.h>

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
#include "BColliderMap.hpp"
#include "BMap.hpp"
#include "pixel_tiles.h"
#include "MAP.h"

#include "pal.h"
#include "img.h"

#include "Mode.hpp"


SpriteSheet	mariolikeSheet((unsigned int *)mariolikeTiles, mariolikeTilesLen,
	pal, palLen,
	96, 160);
//global for game
TBackground	*bg;
TBackground	*bg00;
TBackground	*bg01;
TBackground	*bg02;
TBackground	*bg03;
TBackground	*bg04;
TBackground	*bg05;
TBackground	*bg10;
TBackground	*bg11;
TBackground	*bg12;
TBackground	*bg13;
TBackground	*bg14;
TBackground	*bg15;
Sprite		*a;
BColliderMap	*CMap;
BMap		*bMap;
//bool		jump = false;
//int		dt = 0;
//float		v = 2.;
//int		sx = 0;
//int		bgx = 0;
//vec2f		g_v = {2, 0};
int scrolly = 4*16;
int curmap = 0;
constexpr static int	nbMap = 6;

u16		*maps[nbMap] =
  {
    &Layer10[0],
    &Layer11[0],
    &Layer12[0],
    &Layer13[0],
    &Layer14[0],
    &Layer15[0]
  };


bool		engineInit()
{
	bg = new TBackground(TBackground::MAIN, BgSize_T_512x256, &mariolikeSheet, Layer00, 16, 16, 0);
	bg->scroll(0, scrolly);

//
	BMap	mapBG({16, 16}, {2, 1}, true);
//
	bMap = new BMap({16, 16}, {2, 1}, true);
//	CMap = new BColliderMap(bMap, {16, 16}, {M});
//
	mapBG.init(58);
	bMap->init(0);
	bMap->setMap(0, Layer00);
	bMap->setMap(1, Layer10);
 bg->addInMapT16(Layer00, 16, 16, 0);
 bg->addInMapT16(Layer10, 16, 16, 1);
 // bg2->addInMapT16(mapBG.getData(), 16, 16, 0);
 // bg2->addInMapT16(mapBG.getData(), 16, 16, 1);

	a = new Sprite(Sprite::MAIN, SpriteSize_16x16, &mariolikeSheet, 36 , Sprite::ABSOLUTE);
	a->setPos(0, 0);
//  a->addCollider({1, 1}, {14, 14}, CMap);

	return (true);
}

bool		enginePreUpdate()
{
//	g_v = {v, 0};
//
//	// if (a->getPos().x - sx < 256/2)
//	// 	g_v.x += v / 3.;
//
//	if (jump == true) {
//		dt += 1;
//		if (dt == 50) {
//			dt = 0;
//			jump = false;
//		}
//		else if (a->getCollider()->willCollide({0, -v}) == false)
//			g_v.y -= v;
//	}
//  else if (a->getCollider()->willCollide({0, v + 0.75f}) == false)
//   g_v.y += v + 0.75f;
//	a->setV(g_v.x, g_v.y);
	return (true);
}

void		changeMap(int &bmap)
{
 if (curmap == 6)
 	curmap = 0;
 u16 *map = maps[curmap++];

 bMap->setMap(bmap, map);
 bg->addInMapT16(map, 16, 16, bmap);
 bmap = (bmap + 1) % 2;
}

bool		engineUpdate()
{
//  static int	bmap = 0;
//  static bool	b = false;

 // printf("COUCOU\n");
	static int x = 0;
	bg->scroll(x, scrolly);
	x += 1;
  //bg2->scroll(bgx, 0);
  //bg->scroll(sx, 0);
  //a->scroll(-sx, 0);
//  sx += v;
//  bgx += v / 2 > 0 ? v / 2 : 1;
//  if (b == false && sx >= 256)
//    {
//      changeMap(bmap);
//      b = true;
//    }
//  if (sx >= 512)
//    {
//      a->setPos(a->getPos().x - 512, a->getPos().y);
//      sx = 0;
//      changeMap(bmap);
//      b = false;
//    }
	return (true);
}

//
//void		keyDA()
//{
//  jump = true;
//}
//
//void		keyUA()
//{
//  jump = false;
//  dt = 0;
//}

int		main()
{
	Engine	engine;

	engine.start();
	return (0);
}
