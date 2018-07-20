#pragma once

#include <nds.h>

#include "vec.hpp"

//Block MAP
//this fucking class to all the work here

class BMap
{
private:

  struct d_map
  {
    d_map() = delete;
    d_map(const vec2 &blockSize) : blockSize(blockSize)
    {
      this->data = new u16[blockSize.x * blockSize.y];
      this->alloc = true;
    }
    
    d_map(const vec2 &blockSize, u16 *data) : blockSize(blockSize)
    {
      this->data = data;
      this->alloc = false;
    }
    
    ~d_map()
    {
      if (this->alloc == true)
	delete[] this->data;
    }

    u16	get(int x, int y)
    {
      return (this->data[y * this->blockSize.x + x]);
    }

    u16	get(const vec2 &vec)
    {
      return (this->get(vec.x, vec.y));
    }

    u16		*data;
    bool	alloc;
    const vec2 &blockSize;
  };
  
public:
  BMap(const vec2 &blockSize, const vec2 &size, bool alloc = true);
  BMap(const vec2 &blockSize, const vec2 &size, u16 *data);

  virtual ~BMap();

  u16		get(const vec2 &vec, int bmap) const;
  u16		get(int x, int y, int bmap) const;
  u16		get(const vec2 &vec) const;
  u16		get(int x, int y) const;
  
  void		set(int x, int y, u16 v, int bMap);
  void		set(int x, int y, u16 v);
  void		init(u16 v);
  void		init(u16 v, int bMap);
  
  d_map		*newMap(u16 *data = NULL);

  d_map		getMap(int bMap) const;
  d_map		getMap(int x, int y) const;
  d_map		getMap(const vec2 &vec) const;

  void		setMap(int bMap, u16 *data);
  void		copyMap(int from, int to);
  void		swapMap(int from, int to);
  
  //get
  const vec2	&getSize() const
  {return this->size;}

  const vec2	&getBlockSize() const
  {return this->blockSize;}

  u16		*getData() const
  {return this->data;}

  bool		isAlloc() const
  {return this->alloc;}

  //set
  void		setAlloc(bool alloc)
  {this->alloc = alloc;}

  void		setData(u16 *data)
  {
    if (this->alloc == true)
      delete this->data;
    this->alloc = false;
    this->data = data;
  }
  
private:
  
  u16		*newData() const;
  int		getIdx(int x, int y, int bMap) const;
  int		getIdx(int x, int y) const;
  
private:

  bool		alloc;
  vec2		blockSize;
  vec2		size;
  u16		*data;
};
