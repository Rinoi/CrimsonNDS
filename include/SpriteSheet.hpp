#pragma once

#include <nds.h>

class SpriteSheet
{
  
public:
  
  SpriteSheet(const unsigned int *tiles, unsigned int tilesLen,
	      const unsigned short *pal, unsigned int palLen,
	      unsigned int width, unsigned int height);
  
  virtual ~SpriteSheet();

  void	useIn16(OamState *state);

  void	useInMain16();

  void	useInSub16();

  void	useInMain32();

  void	useInSub32();

  u16	*getIdxMain(u16 idx);

  u16	*getIdxSub(u16 idx);
  
public:
  const unsigned int	*tiles;
  unsigned int		tilesLen;
  const unsigned short	*pal;
  unsigned int		palLen;
  unsigned int		width;
  unsigned int		height;

private:
  bool			bMain;
  bool			bSub;
  u16			**idxMain;
  u16			**idxSub;
};

#define useSpriteSheet(N, w, h)  N(N##Tiles, N##TilesLen,	\
				   N##Pal, N##PalLen, w, h);
