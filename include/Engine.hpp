#pragma once

#include <nds.h>
#include "Sprite.hpp"

bool	__attribute__((weak)) engineInit();
bool	__attribute__((weak)) engineUpdate();
bool	__attribute__((weak)) engineEndUpdate();
bool	__attribute__((weak)) enginePreUpdate();

void	__attribute__((weak)) keyA();
void	__attribute__((weak)) keyB();
void  __attribute__((weak)) keyX();
void  __attribute__((weak)) keyY();
void	__attribute__((weak)) keyStart();
void	__attribute__((weak)) keySelect();
void	__attribute__((weak)) keyDown();
void	__attribute__((weak)) keyLeft();
void	__attribute__((weak)) keyRight();
void	__attribute__((weak)) keyUp();
void	__attribute__((weak)) keyDown();

void	__attribute__((weak)) keyDA();
void  __attribute__((weak)) keyDB();
void  __attribute__((weak)) keyDX();
void  __attribute__((weak)) keyDY();
void  __attribute__((weak)) keyDStart();
void  __attribute__((weak)) keyDSelect();
void	__attribute__((weak)) keyDUp();
void	__attribute__((weak)) keyDDown();
void	__attribute__((weak)) keyDLeft();
void	__attribute__((weak)) keyDRight();

void	__attribute__((weak)) keyUA();
void  __attribute__((weak)) keyUB();
void  __attribute__((weak)) keyUX();
void  __attribute__((weak)) keyUY();
void  __attribute__((weak)) keyUStart();
void  __attribute__((weak)) keyUSelect();
void	__attribute__((weak)) keyUUp();
void	__attribute__((weak)) keyUDown();
void	__attribute__((weak)) keyULeft();
void	__attribute__((weak)) keyURight();

void	__attribute__((weak)) onTouch(touchPosition touch);

class			Engine
{

private:
  static u16		realTime;
  static u16		timeId;
  static bool		bNext;

  static void		timerCallBack();
  
public:
  static u16		getTimeId();
  static bool		isTimeChange();
    
public:
  Engine();
  
  virtual ~Engine();
  
  void	start();
    
public:
  
private:
  bool	init();

  bool	update();

};
