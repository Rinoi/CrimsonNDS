#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet(const unsigned int *tiles, unsigned int tilesLen,
			 const unsigned short *pal, unsigned int palLen,
			 unsigned int width, unsigned int height)
{
  this->tiles = tiles;
  this->tilesLen = tilesLen;
  this->pal = pal;
  this->palLen = palLen;
  this->width = width;
  this->height = height;
  this->bMain = false;
  this->bSub = false;
}

SpriteSheet::~SpriteSheet()
{
}

void  SpriteSheet::useIn16(OamState *state)
{

  if (state == &oamMain)
    {
      if (this->bMain == true)
	return;
      this->bMain = true;
    }
  else
    {
      if (this->bSub == true)
	return;
      this->bSub = true;
    }

  int max = (this->width * this->height) / (16*4);
  (state == &oamMain ? this->idxMain : this->idxSub) = new u16*[max];

  int id = 0;
  for (u_int i = 0; i < this->width * this->height; i += 16*4)
    {
      (state == &oamMain ? this->idxMain : this->idxSub)[id] =
	oamAllocateGfx(state, SpriteSize_16x16, SpriteColorFormat_256Color);

      dmaCopy(this->tiles + i,
	      (state == &oamMain ? this->idxMain : this->idxSub)[id],
	      16*16);

      id += 1;
    }
  dmaCopy(this->pal,
	  state == &oamMain ? SPRITE_PALETTE : SPRITE_PALETTE_SUB,
	  512);
}

void	SpriteSheet::useInMain16()
{
  useIn16(&oamMain);
}

void	SpriteSheet::useInSub16()
{
  useIn16(&oamSub);
}

void	SpriteSheet::useInMain32()
{
  if (this->bMain == true)
    return;
  this->bMain = true;
}


void	SpriteSheet::useInSub32()
{
  if (this->bSub == true)
    return;
  this->bSub = true;
}

u16	*SpriteSheet::getIdxMain(u16 idx)
{
  return (this->idxMain[idx]);
}

u16	*SpriteSheet::getIdxSub(u16 idx)
{
  return (this->idxSub[idx]);
}
