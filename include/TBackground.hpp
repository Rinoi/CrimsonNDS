#pragma once

#include <nds.h>
#include "SpriteSheet.hpp"
#include "BMap.hpp"

class TBackground
{

public:

  enum Type
    {
      MAIN, SUB
    };


public:

  TBackground(const Type &type, BgSize size, SpriteSheet *spriteSheet, int depth = 0);
  TBackground(const Type &type, BgSize size, SpriteSheet *spriteSheet, u16 *map, u_int width, u_int height, int depth = 0);
  virtual ~TBackground();

protected:

  u16		getIdx16(u16 idx);

public:

  void		addInMapT16(int x, int y, u16 idx);
  void		addInMapT16(int x, int y, u16 idx, int bMap);
  void		addInMapT16(u16 *map, u_int width, u_int height, int bMap = 0);
  void		initT16(u16 idx);
  void		initT16(u16 idx, int bMap);

  void		addInMapT32(int x, int y, u16 idx);
  void		addInMapT32(u16 *map, u_int width, u_int height);
  void		initT32(u16 idx);

  void		scroll(int dx, int dy);

  //GET

  u16		*getGfx();
  u16		*getMap();

protected:

  void		init(BgSize size);

protected:

  int		depth;
  int		id;
  Type		type;
  u_int		width;
  u_int		height;
  int		sX;
  int		sY;

  SpriteSheet	*spriteSheet;
  u16		*map;
  BMap		bMap;
};
