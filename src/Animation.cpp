#include "Animation.hpp"
#include "Engine.hpp"

std::list<Animation *>		Animation::animationList;

void				Animation::animationAction(int action, Animation *s)
{
  //UPDATE
  if (action == 0 && Engine::isTimeChange() == true)
    {
      for (std::list<Animation *>::iterator it = Animation::animationList.begin();
	   it != Animation::animationList.end(); it++)
	(*it)->animate();
    }
  //END

  //ADD
  else if (action == 1)
    Animation::animationList.push_back(s);
  //END

  //REMOVE
  else if (action == 2)
    Animation::animationList.remove(s);
  //END
}

void				Animation::animate()
{
  this->timeCurrent -= 1;
  if (this->timeCurrent <= 0)
    {
      this->timeCurrent = this->timeMax;
      this->idxId += 1;
      if (this->idxId >= this->idxTab.size())
	this->idxId = 0;
      this->idx = this->idxTab[this->idxId];
      this->initGfx();
      this->bUpdate = true;
    }

}

Animation::Animation(Type type, SpriteSize size, SpriteSheet *spriteSheet,
		     const std::vector<u16> &idx, int waitingTime) :
  Sprite(type, size, spriteSheet, idx[0])
{
  this->idxTab = idx;
  this->idxId = 0;
  this->timeMax = waitingTime;
  this->timeCurrent = this->timeMax;
  animationAction(1, this);
}

Animation::~Animation()
{
  animationAction(2, this);
}
