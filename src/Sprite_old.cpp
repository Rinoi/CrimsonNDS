// #include "Sprite.hpp"

// #include "Collider.hpp"
// #include "Engine.hpp"

// std::list<Sprite *>  Sprite::spriteList;
// std::list<Sprite *>  Sprite::newSpriteList;

// void		Sprite::SpriteAction(int action, Sprite *s)
// {
//   //UPDATE
//   if (action == 0)
//     {
//       std::list<Sprite *>::iterator it;

//       //LIVE DEATH
//       it = Sprite::spriteList.begin();
//       while (it != Sprite::spriteList.end())
// 	{
// 	  if ((*it)->liveSpan != (u16)(-1) &&
// 	      (*it)->liveSpan != 0 &&
// 	      Engine::isTimeChange())
// 	    (*it)->liveSpan -= 1;
// 	  if ((*it)->liveSpan == 0)
// 	    {
// 	      Sprite *tmp = (*it);
// 	      it = Sprite::spriteList.erase(it);
// 	      delete tmp;
// 	    }
// 	  else
// 	    it++;
// 	}
//       //END

//       //NEW
//       it = Sprite::newSpriteList.begin();
//       while (it != Sprite::newSpriteList.end())
// 	{
// 	  Sprite::spriteList.push_back(*it);
// 	  it = Sprite::spriteList.erase(it);
// 	}

//       //END
      
//       it = Sprite::spriteList.begin();
//       while (it != Sprite::spriteList.end())
// 	{
// 	  if ((*it)->liveSpan != 0)
// 	    // if ((*it)->bUpdate == true || (*it)->bV == true)
// 	      (*it)->update();
// 	  it++;
// 	}
//     }
//   //END

//   //ADD
//   else if (action == 1)
//     Sprite::newSpriteList.push_back(s);
//   //END

//   //REMOVE
//   else if (action == 2)
//     Sprite::spriteList.remove(s);
//   //END
// }

// u16		Sprite::liveAct()
// {
//   return (0);
// }

// Sprite::Sprite(Type type, SpriteSize size, SpriteSheet *spriteSheet, u16 idx) : HasCollider(2)
// {
//   this->type = type;
//   this->size = size;
//   this->typeId = (u16)(-1);
//   this->ptn = {0, 0, 0};
//   this->v = {0., 0., 0.};
//   this->collider = NULL;
//   this->bV = false;
//   this->spriteSheet = spriteSheet;
//   this->idx = idx;
//   this->bUpdate = true;
//   this->fCollider = NULL;
//   this->personalId = 0;
//   this->scroll = {0, 0};
//   this->liveSpan = (u16)(-1);
//   this->init();
// }

// Sprite::~Sprite()
// {
//   if (this->collider != NULL)
//     delete collider;
//   oamClearSprite(this->type == MAIN ? &oamMain : &oamSub,
// 		 this->id);
//   this->SpriteAction(2, this);
//   getNewId(this->id);
// }

// void		Sprite::addCollider(const t_ptn &add, const t_ptn &size, ColliderMap *map)
// {
//   this->collider = new Collider(&this->ptn, add, size, map, this);
// }

// void		Sprite::move()
// {
//   if (this->bV == false)
//     return ;
//   if (this->collider == NULL)
//     {
//       this->ptn.x += this->v.x;
//       this->ptn.y += this->v.y;
//     }
//   else
//     {
//       int i = 1;
//       bool b = false;
//       ColliderTest *cTest = NULL;
//       static ColliderTile *colliderTile = NULL;

//       if (colliderTile == NULL)
// 	colliderTile = new ColliderTile(0, {0, 0});
//       while ((int)(this->v.x / i) != 0 || (int)(this->v.y / i) != 0)
//       	{
// 	  if (this->collider->willCollide({this->v.x / i, this->v.y / i, 0}) == false)
// 	    {
// 	      this->ptn.x += this->v.x / i;
// 	      this->ptn.y += this->v.y / i;
// 	      // break;
// 	    }
// 	  else if (this->fCollider != NULL)
// 	    {
// 	      cTest = this->collider->getTest({this->v.x / i, this->v.y / i, 0});
// 	      b = true;
// 	    }
// 	  i += 1;
// 	}
//       if (this->fCollider != NULL && b == true && cTest != NULL)
// 	{
// 	  this->fCollider(this, cTest->objOn);
// 	}

//     }

// }

// bool		Sprite::update()
// {
//   int		x = this->ptn.x - this->scroll.x;
//   int		y = this->ptn.y - this->scroll.y;
//   this->move();
//   this->bUpdate = false;
//   if (x < -16 || x > 256 + 16 || y < -16 || y > 192 + 16)
//     oamSetHidden(this->type == MAIN ? &oamMain : &oamSub,
// 		 this->id,
// 		 true);
//   else
//     {
//       oamSetHidden(this->type == MAIN ? &oamMain : &oamSub,
// 		   this->id,
// 		   false);
//       oamSet(this->type == MAIN ? &oamMain : &oamSub,
// 	     this->id,
// 	     x,
// 	     y,
// 	     2,
// 	     0,
// 	     this->size,
// 	     SpriteColorFormat_256Color,
// 	     this->gfx,
// 	     -1,
// 	     false,
// 	     false,
// 	     false, false,
// 	     false
// 	     );
//     }
//   return (true);
// }

// t_ptn		Sprite::getPos() const
// {
//   t_ptn		ptn = this->ptn;

//   ptn.x += this->width / 2 - this->scroll.x;
//   ptn.y += this->height / 2 - this->scroll.y;
//   return (ptn);
// }

// void		Sprite::setPtn(int x, int y)
// {
//   this->ptn.x = x;
//   this->ptn.y = y;
//   this->bUpdate = true;
// }

// void		Sprite::setIdx(u16 idx)
// {
//   this->idx = idx;
//   this->initGfx();
//   this->bUpdate = true;
// }

// void		Sprite::setV(float x, float y)
// {
//   this->bV = true;
//   this->v.x = x;
//   this->v.y = y;
//   if (this->v.x == 0. && this->v.y == 0)
//     this->bV = false;
// }

// void		Sprite::setLiveSpan(u16 liveSpan)
// {
//   this->liveSpan = liveSpan;
// }

// void		Sprite::initGfx()
// {
//   if (this->type == Sprite::MAIN)
//     {
//       this->spriteSheet->useInMain16();
//       this->gfx = this->spriteSheet->getIdxMain(this->idx);
//     }
//   else
//     {
//       this->spriteSheet->useInSub16();
//       this->gfx = this->spriteSheet->getIdxSub(this->idx);
//     }
// }

// bool		Sprite::init()
// {
//   this->width = 16;
//   this->height = 16;
//   this->initGfx();
//   this->id = this->getNewId();
//   this->SpriteAction(1, this);
//   return (true);
// }

// u16		Sprite::getNewId(int act)
// {
//   static bool b = false;
//   static bool mainId[128];
//   static bool subId[128];
//   bool        *tab;
//   int         i = 0;

//   //INIT
//   if (b == false)
//     {
//       b = true;
//       for (int i = 0; i < 128; i += 1)
// 	{
// 	  mainId[i] = false;
// 	  subId[i] = false;
// 	}
//     }
//   //END

//   if (this->type == Sprite::MAIN)
//     tab = mainId;
//   else
//     tab = subId;

//   if (act != -1)
//     {
//       tab[act] = false;
//       return (act);
//     }

//   while (i < 128)
//     {
//       if (tab[i] == false)
// 	{
// 	  tab[i] = true;
// 	  break;
// 	}
//       i += 1;
//     }
//   if (i >= 128)
//     return (127);
//   return (i);
// }
// 
