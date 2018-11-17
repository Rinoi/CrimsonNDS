#include "Engine.hpp"
#include "Animation.hpp"
#include "Mode.hpp"
#include "Sprite.hpp"

#include <nds.h>
#include <stdio.h>

u16		Engine::realTime = 0;
u16		Engine::timeId = 0;
bool		Engine::bNext = false;

extern int g_id;

void Engine::timerCallBack()
{
  Engine::realTime = (Engine::realTime + 1) % 8;
}
  
Engine::Engine()
{

}

Engine::~Engine()
{

}


u16		Engine::getTimeId()
{
  return (Engine::timeId);
}

bool		Engine::isTimeChange()
{
  return (Engine::bNext);
}

void		Engine::start()
{
  this->init();
  while (this->update());
}

PrintConsole top;
PrintConsole bot;

bool		Engine::init()
{
  timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(8), Engine::timerCallBack);

  GMode::setCurrent<ModeA>();
    
  oamInit(&oamMain, SpriteMapping_1D_128, false);
  oamInit(&oamSub, SpriteMapping_1D_128, false);

  if (engineInit && engineInit() == false)
    return (false);

  return (true);
}

bool		Engine::update()
{
  int		keys = 0;
  u16		time = this->realTime;

  this->bNext = false;
  if (this->timeId != time)
    {
      this->timeId = time;
      this->bNext = true;
    }

  GMode::current->startUpdate();
  
  if (enginePreUpdate && enginePreUpdate() == false)
    return (false);
    
  scanKeys();

  
  //KEY UP
  keys = keysUp();
  if((keys & KEY_A) && keyUA)
    keyUA();
  if((keys & KEY_B) && keyUB)
    keyUB();
  if((keys & KEY_UP) && keyUUp)
    keyUUp();
  if((keys & KEY_DOWN) && keyUDown)
    keyUDown();
  if((keys & KEY_LEFT) && keyULeft)
    keyULeft();
  if((keys & KEY_RIGHT) && keyURight)
    keyURight();
  //KEY UP

  //KEY DOWN
  keys = keysDown();
  if((keys & KEY_A) && keyDA)
    keyDA();
  if((keys & KEY_B) && keyDB)
    keyDB();
  if((keys & KEY_UP) && keyDUp)
    keyDUp();
  if((keys & KEY_DOWN) && keyDDown)
    keyDDown();
  if((keys & KEY_LEFT) && keyDLeft)
    keyDLeft();
  if((keys & KEY_RIGHT) && keyDRight)
    keyDRight();
  //KEY DOWN

  //KEY
  keys = keysHeld();
  if((keys & KEY_UP) && keyUp)
    keyUp();
  if((keys & KEY_DOWN) && keyDown)
    keyDown();
  if((keys & KEY_LEFT) && keyLeft)
    keyLeft();
  if((keys & KEY_RIGHT) && keyRight)
    keyRight();
  if((keys & KEY_A) && keyA)
    keyA();
  if((keys & KEY_B) && keyB)
    keyB();
  //KEY


  if((keys & KEY_TOUCH) && onTouch)
    {
      touchPosition touch;
      
      touchRead(&touch);
      onTouch(touch);
    }

  
  if (engineUpdate && engineUpdate() == false)
    return (false);

  Animation::animationAction(0);
  // Sprite::SpriteAction(0);
  
  Sprite::updateSprites();

  if (engineEndUpdate && engineEndUpdate() == false)
    return (false);

  
  swiWaitForVBlank();

  bgUpdate();
  oamUpdate(&oamMain);
  oamUpdate(&oamSub);

  GMode::current->endUpdate();


  return (true);
}
