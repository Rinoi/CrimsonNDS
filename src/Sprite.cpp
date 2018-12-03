#include "Sprite.hpp"
#include "Engine.hpp"

#include "Collider.hpp"
#include "ColliderMap.hpp"

#include <cstdio>

//STATIC

bool			Sprite::initSprites()
{
  if (b == false)
    {
      b = true;
      for (int i = 0; i < 128; i += 1)
	{
	  mainId[i] = false;
	  subId[i] = false;
	}
    }
  return (true);
}

bool			Sprite::updateSprites()
{
  std::list<Sprite *>::iterator it;

  //LIVE AND DEATH
  it = Sprite::spriteList.begin();
  while (it != Sprite::spriteList.end())
    {
      if ((*it)->lifeSpan != (u16)(-1) &&
      	  (*it)->lifeSpan != 0 &&
      	  Engine::isTimeChange())
      	(*it)->lifeSpan -= 1;
      if ((*it)->lifeSpan == 0)
	{
	  Sprite *tmp = (*it);

	  it = Sprite::spriteList.erase(it);

	  delete tmp;
	}
      else
	it++;
    }
  //END

  //ADD NEW
  it = Sprite::newSpriteList.begin();
  while (it != Sprite::newSpriteList.end())
    {
      Sprite::spriteList.push_back(*it);
      it = Sprite::spriteList.erase(it);
    }

  //END

  //UPDATE
  it = Sprite::spriteList.begin();
  while (it != Sprite::spriteList.end())
    {
      // if ((*it)->bUpdate == true || (*it)->bV == true)
      (*it)->update();
      it++;
    }
  //END
  return (true);
}

bool			Sprite::b = false;
bool			Sprite::mainId[128];
bool			Sprite::subId[128];

std::list<Sprite *>	Sprite::spriteList;
std::list<Sprite *>	Sprite::newSpriteList;


//MAIN

Sprite::Sprite(Type type, SpriteSize size, SpriteSheet *spriteSheet, u16 idx,
		       Reference ref)
{
  this->type = type;
  this->spriteSize = size;
  this->spriteSheet = spriteSheet;
  this->idx = idx;
  this->ref = ref;

  this->pos = {0, 0};
  this->v = {0.0, 0.0};
  this->lifeSpan = -1;

  this->bUpdate = true;
  this->collider = NULL;
  this->init();
}

Sprite::Sprite(Type type, SpriteSize size, SpriteSheet *spriteSheet, u16 idx, int x, int y
		       ,Reference ref)
{
  this->type = type;
  this->spriteSize = size;
  this->spriteSheet = spriteSheet;
  this->idx = idx;
  this->ref = ref;

  this->pos = {x, y};
  this->v = {0.0, 0.0};
  this->lifeSpan = -1;

  this->bUpdate = true;
  this->collider = NULL;
  this->init();
}

Sprite::~Sprite()
{
  if (this->collider != NULL)
    delete this->collider;

  oamClearSprite(this->type == MAIN ? &oamMain : &oamSub,
		 this->id);
  (this->type == Sprite::MAIN ? mainId : subId)[this->id] = false;

}


void			Sprite::setSize()
{
  switch (this->spriteSize)
    {
    case SpriteSize_8x8   : this->size = {8, 8}; break;
    case SpriteSize_16x16 : this->size = {16, 16}; break;
    case SpriteSize_32x32 : this->size = {32, 32}; break;
    case SpriteSize_64x64 : this->size = {64, 64}; break;
    case SpriteSize_16x8  : this->size = {16, 8}; break;
    case SpriteSize_32x8  : this->size = {32, 8}; break;
    case SpriteSize_32x16 : this->size = {32, 16}; break;
    case SpriteSize_64x32 : this->size = {64, 32}; break;
    case SpriteSize_8x16  : this->size = {8, 16}; break;
    case SpriteSize_8x32  : this->size = {8, 32}; break;
    case SpriteSize_16x32 : this->size = {16, 32}; break;
    case SpriteSize_32x64 : this->size = {32, 64}; break;
    }
}

bool			Sprite::init()
{
  this->id = this->getNewId();

  Sprite::newSpriteList.push_back(this);
  this->initGfx();
  this->update();

  return (true);
}

void			Sprite::initGfx()
{
  if (this->type == Sprite::MAIN)
    {
      this->spriteSheet->useInMain16();
      this->gfx = this->spriteSheet->getIdxMain(this->idx);
    }
  else
    {
      this->spriteSheet->useInSub16();
      this->gfx = this->spriteSheet->getIdxSub(this->idx);
    }
}

bool			Sprite::update()
{
  this->move();

  if (this->bUpdate == true)
    {
      this->bUpdate = false;

      oamSet(this->type == MAIN ? &oamMain : &oamSub,
	     this->id,
	     (int)(this->pos.x + this->pScroll.x) % 256,
	     (int)(this->pos.y + this->pScroll.y) % 256,
	     2,
	     0,
	     this->spriteSize,
	     SpriteColorFormat_256Color,
	     this->gfx,
	     -1,
	     false,
	     false,
	     false, false,
	     false
	     );
    }
  return (true);
}

u16			Sprite::getNewId()
{
  bool			*tab;
  int			i = 0;

  if (this->type == Sprite::MAIN)
    tab = mainId;
  else
    tab = subId;
  while (i < 128)
    {
      if (tab[i] == false)
	{
	  tab[i] = true;
	  break;
	}
      i += 1;
    }
  if (i >= 128)
    return (127);
  return (i);
}

void			Sprite::move()
{
  vec2f			v = this->v;

  if (this->collider != NULL)
    {
      if (this->collider->willCollide({0, 0}) == true)
	goto deplace;
      if (this->collider->willCollide(v) == true)
	{
	  // printf("o => %f %f\n", v.x, v.y);
	  v.x = 0;
	  // printf("test\n");
	  for (int i = 0; i < 4; i += 1)
	    {
	      // printf("%d %f\n", i, v.y);
	      if (this->collider->willCollide(v) == false)
		{
		  // printf("%f\n", v.y);
		  goto deplace;
		}
	      v.y /= 2;
	    }
	}
      else
	goto deplace;
    }
  else
    {
    deplace:
      this->pos.x += v.x;
      this->pos.y += v.y;
      this->bUpdate = true;
    }
}

void			Sprite::addCollider(const vec2f &add, const vec2f &size,
					    IColliderMap *colliderMap, u16 objId)
{
  if (this->collider != NULL)
    delete this->collider;
  this->collider = new Collider(this->pos, add, size, colliderMap, this, objId);
}

void			Sprite::setPos(const vec2f &pos)
{
  this->pos = pos;
  this->bUpdate = true;
}

void			Sprite::setPos(float x, float y)
{
  this->pos.x = x;
  this->pos.y = y;
  this->bUpdate = true;
}

void			Sprite::scroll(int dx, int dy)
{
  this->pScroll.x = dx;
  this->pScroll.y = dy;
  this->bUpdate = true;
}

void			Sprite::setV(const vec2f &v)
{
  this->v = v;
  this->bUpdate = true;
}

void			Sprite::setV(float x, float y)
{
  this->v.x = x;
  this->v.y = y;
  this->bUpdate = true;
}

void			Sprite::setIdx(u16 idx)
{
  this->idx = idx;
  this->initGfx();
  this->bUpdate = true;
}

void			Sprite::destroy()
{
  this->lifeSpan = 0;
}
