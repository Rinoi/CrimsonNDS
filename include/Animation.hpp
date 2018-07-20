#pragma once

#include <vector>
#include <nds.h>

#include "Sprite.hpp"

class Animation : public Sprite
{

private:

  static std::list<Animation *>	animationList;
  
public:

  static u16			getAnimationId(int id = -1);
  
  static void			animationAction(int action, Animation *s = NULL);

private:

  void				animate();
  
public:

  Animation(Type type, SpriteSize size, SpriteSheet *spriteSheet,
	    const std::vector<u16> &idx, int waitingTime);

  virtual ~Animation();

  void				setTab(const std::vector<u16> &tab)
  {this->idxTab = tab;}
  
private:

  std::vector<u16>		idxTab;
  u_int				idxId;
  
  int				timeMax;
  int				timeCurrent;
  
};
