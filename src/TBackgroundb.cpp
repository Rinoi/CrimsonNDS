#include "TBackgroundb.hpp"
#include <stdio.h>

int	gb_id = 0;

TBackgroundb::TBackgroundb(const Type &type, BgSize size, SpriteSheet *spriteSheet, int depth, u16 **maps) :
  bMap({2, 2}, {16, 16}, false)
{
    this->maps = maps;
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
  this->id += this->type == TBackgroundb::MAIN ? 0 : 4;
  bgShow(this->id);
  gb_id = this->id;
  bgSetPriority(this->id, 3 - this->depth);
  init(size);
}

TBackgroundb::TBackgroundb(const Type &type, BgSize size, SpriteSheet *spriteSheet, u16 *map, u_int width, u_int height, int depth, u16 **maps) :
  bMap({8, 8}, {32, 32}, false)
{

    this->maps = maps;
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
  this->id += this->type == TBackgroundb::MAIN ? 0 : 4;
  bgShow(this->id);
  gb_id = this->id;
  bgSetPriority(this->id, 3 - this->depth);
  init(size);
  addInMapT16(map, width, height);
}

TBackgroundb::~TBackgroundb()
{
  bgHide(this->id);
}

u16		TBackgroundb::getIdx16(u16 idx)
{
  u16		r = 0;
  int		w = this->spriteSheet->width / 16;

  if (idx == 0)
    return r;

  //y
  if (idx >= w)
    {
      int h = idx / w;

      if (h % 2 == 0)
	r = (h  / 2) * 16 * (w / 2);
      else
	r = ((h - 1)  / 2) * 16 * (w / 2) + 8;
      idx %= w;
    }
  //x
  if (idx == 0)
    return r;
  if (idx % 2 == 0)
    r += (idx  / 2) * 16;
  else
    r += ((idx - 1) / 2) * 16 + 2;
  return (r);
}


//WHY ???????
// DS can only draw 8x8 pixel tiles at once
// So we have a map of 32x32(256 pixel) id of each 8x8 pixel it need to draw
void		TBackgroundb::addInMapT16(int x, int y, u16 idx)
{
  int		bMap = 0;

  if (x >= 256 / 16)
    {
      bMap += 1;
      x -= 256 / 16;
    }
  if (y >= 256 / 16)
    {
      bMap += 2;
      y -= 256 / 16;
    }
  return (this->addInMapT16(x, y, idx, bMap));
}

// void		TBackground::addInMapT16(int x, int y, u16 idx, int bMap)
// {
//   const int	w = 2;
//   const int	h = 2;
//   int		i = y * 32 * w + x * h;

//   idx *= w * h;
//   printf("%d => ", i);
//   this->bMap.set(x * w, y * h , 0, idx);
//   // for (int dx = 0; dx < w; dx += 1)
//   //   for (int dy = 0; dy < h; dx += 1)
//   //     {
//   // 	idx += 1;
//   //     }
// }

void		TBackgroundb::addInMapT16(int x, int y, u16 idx, int bMap)
{
  const int	w = 2;
  const int	h = 2;
  int		i = y * 32 * w + x * h;

  idx *= w * h;
  for (int b = 0; b < 2; b += 1)
    {
      this->map[i + (0x00000400 * bMap) + 0] = idx;
      this->map[i + (0x00000400 * bMap) + 1] = idx + 1;
      // this->map[i + 2] = idx + 2;
      // this->map[i + 3] = idx + 3;

      idx += w;
      i += 32;
    }
}

void		TBackgroundb::addInMapT16(u16 *map, u_int width, u_int height, int bMap)
{
  for (u_int y = 0; y < height; y += 1)
    for (u_int x = 0; x < width; x += 1)
      {
	this->addInMapT16(x, y, map[y * width + x], bMap);
      }
}

void		TBackgroundb::initT16(u16 idx)
{
  for (u_int y = 0; y < this->height / 16; y += 1)
    for (u_int x = 0; x < this->width / 16; x += 1)
      this->addInMapT16(x, y, idx);
}

void		TBackgroundb::initT16(u16 idx, int bMap)
{
  for (u_int y = 0; y < 256 / 16; y += 1)
    for (u_int x = 0; x < 256 / 16; x += 1)
      this->addInMapT16(x, y, idx, bMap);
}

void		TBackgroundb::addInMapT32(int x, int y, u16 idx)
{  
  int		i = y * 32 * 4 + x * 4;

  idx *= 16;
  for (int b = 0; b < 4; b += 1)
    {
      this->map[i] = idx;
      this->map[i + 1] = idx + 1;
      this->map[i + 2] = idx + 2;
      this->map[i + 3] = idx + 3;

      idx += 4;
      i += 32;
    }
}

void		TBackgroundb::addInMapT32(u16 *map, u_int width, u_int height)
{
  for (u_int y = 0; y < height; y += 1)
    for (u_int x = 0; x < width; x += 1)
      this->addInMapT32(x, y, map[y * height + x]);
}


void		TBackgroundb::initT32(u16 idx)
{
  for (u_int y = 0; y < height / 32; y += 1)
    for (u_int x = 0; x < width / 32; x += 1)
      this->addInMapT32(x, y, idx);
}

//GET

u16		*TBackgroundb::getGfx()
{
  return (bgGetGfxPtr(this->id));
}

u16		*TBackgroundb::getMap()
{
  return (this->map);
}

void		TBackgroundb::scroll(int dx, int dy)
{
  bgSetScroll(this->id, dx, dy);
}

void		TBackgroundb::init(BgSize size)
{
  this->map = bgGetMapPtr(this->id);
  this->bMap.setData(this->map);
  this->width = 256;
  this->height = 256;

  if (size == BgSize_T_512x256 || size == BgSize_T_512x512)
    this->width = 512;
  if (size == BgSize_T_256x512 || size == BgSize_T_512x512)
    this->height = 512;

  // if (this->type == TBackground::MAIN)
  dmaCopy(this->spriteSheet->tiles, bgGetGfxPtr(this->id), this->spriteSheet->tilesLen);
  
  // if (this->type == TBackground::MAIN)
  //   {
  if (this->type == TBackgroundb::MAIN)
    dmaCopy(this->spriteSheet->pal, BG_PALETTE, this->spriteSheet->palLen);
  else
    dmaCopy(this->spriteSheet->pal, BG_PALETTE_SUB, this->spriteSheet->palLen);
  // dmaCopy(this->spriteSheet->pal, BG_PALETTE_SLOT1, this->spriteSheet->palLen);
  // dmaCopy(this->spriteSheet->pal, BG_PALETTE_SLOT2, this->spriteSheet->palLen);
  // dmaCopy(this->spriteSheet->pal, BG_PALETTE_SLOT3, this->spriteSheet->palLen);
  // }
  //   else
  //     dmaCopy(this->spriteSheet->pal, BG_PALETTE_SUB, this->spriteSheet->palLen);

  u16 *palette = BG_PALETTE;
  // //set up the palette for color printing
  // palette[1 * 16 - 1] = RGB15(0,0,0); //30 normal black
  // palette[2 * 16 - 1] = RGB15(15,0,0); //31 normal red
  // palette[3 * 16 - 1] = RGB15(0,15,0); //32 normal green
  // palette[4 * 16 - 1] = RGB15(15,15,0); //33 normal yellow

  // palette[5 * 16 - 1] = RGB15(0,0,15); //34 normal blue
  // palette[6 * 16 - 1] = RGB15(15,0,15); //35 normal magenta
  // palette[7 * 16 - 1] = RGB15(0,15,15); //36 normal cyan
  // palette[8 * 16 - 1] = RGB15(24,24,24); //37 normal white

  // palette[9 * 16 - 1 ] = RGB15(15,15,15); //40 bright black
  // palette[10 * 16 - 1] = RGB15(31,0,0); //41 bright red
  // palette[11 * 16 - 1] = RGB15(0,31,0); //42 bright green
  // palette[12 * 16 - 1] = RGB15(31,31,0);   //43 bright yellow

  // palette[13 * 16 - 1] = RGB15(0,0,31); //44 bright blue
  // palette[14 * 16 - 1] = RGB15(31,0,31);   //45 bright magenta
  // palette[15 * 16 - 1] = RGB15(0,31,31);   //46 bright cyan
  // palette[16 * 16 - 1] = RGB15(31,31,31); //47 & 39 bright white

}

void            TBackgroundb::changeMap(int &bmap, int curmap)
{
    if (curmap == 6)
	curmap = 0;
    u16    *map = maps[curmap++];
    
    this->bMap.setMap(bmap, map);
    this->addInMapT16(map, 16, 16, bmap);
    //CMap = new BColliderMap(bMap, {16, 16}, {3,4,5,7,8,9,10,11,12,13,14,15,16,17,21,22,23,28,29});                                                                                                           
    //a->addCollider({1, 1}, {14, 14}, CMap);                                                                                                                                                                  

 bmap = (bmap + 1) % 2;
 // printf("change %p\n", map);                                                                                                                                                                             
}
