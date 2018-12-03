#include "TBackground2.hpp"
#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>


TBackground2::TBackground2(const Type &type, BgSize size, SpriteSheet *spriteSheet, int depth, u16 *maps[]) :
  bMap({2, 2}, {16, 16}, false, NULL)
{
    this.maps = maps;
    this->type = type;
    this->depth = depth;
    this->spriteSheet = spriteSheet;
  // if (this->type == TBackground::MAIN)
  //   this->id = bgInit(this->depth, BgType_Text8bpp, size, this->depth, 1);
  // else
  //   //    else if (this->type == TBackground::SUB)
  //   this->id = bgInitSub(this->depth, BgType_Text8bpp, size, this->depth, 1);
  // this->id = bgInit(this->depth, BgType_Text8bpp, size, 5, 2);
  // this->id = bgInit(3 - this->depth, BgType_Text8bpp, size, 5, 2);
  this->id = this->depth;
  this->id += this->type == TBackground::MAIN ? 0 : 4;
  bgShow(this->id);
  g_id = this->id;
  bgSetPriority(this->id, 3 - this->depth);
  init(size);
}


void		TBackground2::changeMap(int &bmap, int curmap)
{
//	if (curmap == 6)
//		curmap = 0;
  u16	*map = this.maps[curmap];

  bMap->setMap(bmap, map);
  bg->addInMapT16(map, 16, 16, bmap);
  //CMap = new BColliderMap(bMap, {16, 16}, {3,4,5,7,8,9,10,11,12,13,14,15,16,17,21,22,23,28,29});
  //a->addCollider({1, 1}, {14, 14}, CMap);

  bmap = (bmap + 1) % 2;
  // printf("change %p\n", map);
}