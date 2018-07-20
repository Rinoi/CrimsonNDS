#pragma once

#include <iostream>

class		IGraphicMode
{
public:
  virtual	~IGraphicMode() = default;

  virtual bool		run() = 0;

  virtual void		startUpdate() = 0;
  virtual void		endUpdate() = 0;
};

class		GMode
{
public:
  GMode() = delete;

  template<typename T>
  static IGraphicMode	*setCurrent()
  {
    return (setCurrent(new T()));
  }
  
  static IGraphicMode	*setCurrent(IGraphicMode *mode)
  {
    if (current != NULL)
      delete current;
    current = mode;
    current->run();
    return (current);
  }
  
  static IGraphicMode	*current;
};
